// Fill out your copyright notice in the Description page of Project Settings.


#include "CCharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerInput.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Item/CMyWeapon.h"
#include "Components/SceneComponent.h"
#include "InputCore.h"
#include "TimerManager.h"
#include "FSM/PlayerStateBase.h"
//#include "FSM/OBJECT_STATE/OFSMCollection.h"
#include "AnimInstance\KwangAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/App.h"
//#include "FSM/S_IDLE_NEWA.h"
#include "NiagaraSystem.h"
#include "FSM/PlayerStateFactory.h"
#include "FSM/OBJECT_STATE/OFSMCollection.h"
#include "Components/AttributeComponent.h"
#include "Components/HealthBarComponent.h"
#include "HUD/PlayerHUD.h"
#include "HUD/PlayerOverlay.h"
#include "Components/InventoryComponent.h"
#include "HUD/MenuWidget.h"
#include "Enemy/Sojeongbang.h"
#include "Components/SlateTest.h"


ACCharacterPlayer::ACCharacterPlayer()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));//엔진에 기본적으로 내장되어있는 카메라 요소를 생성 이름도 설정
	CameraBoom->SetupAttachment(RootComponent);//루트 오브젝트에 붙여둠
	CameraBoom->TargetArmLength = 400.0f;//팔길이
	CameraBoom->bUsePawnControlRotation = true;//폰의 회전을 따라서 갈 것인가
	CameraBoom->bInheritPitch = true;
	CameraBoom->bInheritYaw = true;
	CameraBoom->bInheritRoll= false;
	


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);//붙이고 SocketName는 'springarmendpoint'라고 지정되어 있음
	Camera->bUsePawnControlRotation = false;//카메라가 붐에 따라서 간다면 카메라의 회전이 달라짐
	
	//AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	//UNiagaraSystem::create
	//currentState = ECharacterState::S_IDLE;
	//previousState = ECharacterState::S_IDLE;
	moveSpeed = 1000.0f;
	
	WaitFrame = 0;
	//bTrigger = false;
	PrimaryActorTick.bCanEverTick = true;
	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attribute"));
	InventoryWidget = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(RootComponent);

}

ACCharacterPlayer::~ACCharacterPlayer()
{
}

void ACCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	bIsDie = false;
	//player키 입력
	PlayerController = CastChecked<APlayerController>(GetController());

	FString mapName = GetWorld()->GetMapName();
	FString SmapName=FPackageName::GetShortName(mapName);
	FString clearmap = "GuardianAI";

	InitializePlayerOverlay();
	
	if (mapName.Contains(clearmap))
	{
		PlayerOverlay->SetVisibility(ESlateVisibility::Hidden);
	}

	Restart= CreateWidget<UMenuWidget>(GetWorld(), RestartClass);
	Clear= CreateWidget<UMenuWidget>(GetWorld(), ClearClass);
	//Clear->AddToViewport();
	//Restart->AddToViewport();
	//InteractionWidget = CreateWidget<UItemWidget>(GetWorld(), InteractionClass);
	//Restart = CreateDefaultSubobject<UMenuWidget>(TEXT("Restart"));
	//KeyMappingArray = PlayerContext->GetMappings();
	FName WeaponSocket(TEXT("S_Sheath"));
	if (MyWeapon)
	{
		Weapon = GetWorld()->SpawnActor<ACMyWeapon>(MyWeapon, FVector::ZeroVector, FRotator::ZeroRotator);
		Weapon->SetOwner(this);
	}
	//무기 손에 붙이기
	if (Weapon)
	{
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	}

	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlayerContext, 0);
	}
	check(EnhancedInputComponent != nullptr&&"you don't allow EnhancedInputComponent");
	//check(bWasInitialized && "Did you forget to call Init()?");
	//LateBeginPlay();
	//SimulateSpaceKeyPress(FName("Jump"),EKeys::SpaceBar);
	MoveActionBinding = &EnhancedInputComponent->BindActionValue(MovementAction);
	LookActionBinding = &EnhancedInputComponent->BindActionValue(LookAction);
	
	bIsSheath = true;
	stateFactory = NewObject<UPlayerStateFactory>();
	stateFactory->Set(this);
	stateFactory->AddToRoot();
	curState = stateFactory->CreateNORMAL();
	curState->EnterStates();
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASojeongbang::StaticClass(), FoundActors);
	 //Cast<ASojeongbang>(FoundActors.begin());
	if (FoundActors.IsValidIndex(0))
	{
		Boss = Cast<ASojeongbang>(FoundActors[0]);
		//Boss->MyStandardDelegate.BindUObject(this->PlayerOverlay, &UPlayerOverlay::ShowBossHp);
		Boss->MyParamDelegate.BindUObject(this->PlayerOverlay, &UPlayerOverlay::SetVisiblityBossHp);
		/*SlateTest temp;
		GEngine->GameViewport->AddViewportWidgetForPlayer(Cast<ULocalPlayer>(getPlayerController()), temp.Create(),1);*/
	}
	
	//curState = stateFactory->CreateS_IDLE();
	//curState = NewObject<AS_IDLE_NEWA>();
	//new S_IDLE();
}

void ACCharacterPlayer::InitializePlayerOverlay()
{
	
	if (PlayerController)
	{
		APlayerHUD* PlayerHUD = Cast<APlayerHUD>(PlayerController->GetHUD());
		if (PlayerHUD)
		{
			PlayerOverlay = PlayerHUD->GetPlayerOverlay();
			if (PlayerOverlay)
			{
				PlayerOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
				PlayerOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
			}
		}

	}
}


void ACCharacterPlayer::SimulateSpaceKeyPress(const FName name)
{
	if (!PlayerController->IsInputKeyDown(key))
	{
		PlayerController->InputKey(key, EInputEvent::IE_Pressed, 1.0f, false);

		FTimerHandle ReleaseHandle;
		FTimerDelegate ReleaseDelegate;

		ReleaseDelegate.BindUObject(this, &ACCharacterPlayer::OnReleaseKey); 
		PlayerController->GetWorldTimerManager().SetTimer(ReleaseHandle, ReleaseDelegate, 2.0f, false);

	}
}

void ACCharacterPlayer::OnReleaseKey() 
{
	PlayerController->InputKey(key, EInputEvent::IE_Released, 1.0f, false);
}
const FInputActionValue ACCharacterPlayer::GetMoveInputActionValue()
{
	return MoveActionBinding->GetValue();
}
const FInputActionValue ACCharacterPlayer::GetLookInputActionValue()
{
	return LookActionBinding->GetValue();
}

UPlayerStateBase* ACCharacterPlayer::GetCurPlayerState()
{
	//UE_LOG(LogTemp, Warning, TEXT("curState class: %s"), (this->curState)->_getUObject());
	return curState;
}

void ACCharacterPlayer::WaitFramePassing()
{
	WaitFrame = WaitFrame - FApp::GetDeltaTime() * 4;
}

UKwangAnimInstance* ACCharacterPlayer::getAnimInstance()
{
	if (GetMesh()->GetAnimInstance())
	{
		UAnimInstance* instance = GetMesh()->GetAnimInstance();
		UKwangAnimInstance* kwang = Cast<UKwangAnimInstance>(instance);
		return kwang;
	}
	return NULL;
}

const TObjectPtr<class ACMyWeapon> ACCharacterPlayer::GetWeapon()
{
	return Weapon;
}
void ACCharacterPlayer::SetKey(FKey _key)
{
	key = _key;
}

//void ACCharacterPlayer::changeState(ECharacterState inState)
//{
//	
//	setPreviousState();
//	//Destroy(curState);
//
//	curState->exit(*this);
//	curState->enter(*this);
//	currentState = inState;
//}
//ECharacterState ACCharacterPlayer::getCurState()
//{
//	return currentState;
//}
//void ACCharacterPlayer::setCurState(ECharacterState state)
//{
//	currentState = state;
//}
APlayerController* ACCharacterPlayer::getPlayerController()
{
	return PlayerController;
}


void ACCharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if (stateFactory->context == NULL)
	//{
	//	stateFactory->Set(this);
	//}
	if (Attributes)
	{
		if (!bIsUsingStamina)
		{
			Attributes->RegenStamina(DeltaTime);
			PlayerOverlay->SetStaminaBarPercent(Attributes->GetStaminaPercent());
		}
	}
	update();
}
void ACCharacterPlayer::BossHpUpdate(float percent)
{
	int type = 0;
	
	if (percent == 0) {
		type = 0;
	}
	else if (percent > 0 && percent <= 0.125) {
		type = 1;
	}
	else if (percent > 0.125 && percent <= 0.25) {
		type = 2;
	}
	else if (percent > 0.25 && percent <= 0.375) {
		type = 3;
	}
	else if (percent > 0.375 && percent <= 0.5) {
		type = 4;
	}
	else if (percent > 0.5 && percent <= 0.625) {
		type = 5;
	}
	else if (percent > 0.625 && percent <= 0.75) {
		type = 6;
	}
	else if (percent > 0.75 && percent <= 0.875) {
		type = 7;
	}
	else if (percent > 0.875 && percent <= 1) {
		type = 8;
	}
	//switch (static_cast<int>(percent * 8))
	//{ // 8개 구간으로 나누기 위해 8을 곱함
	//case 0:
	//	type = 0;
	//	break;
	//case 1:
	//	type = 1;
	//	break;
	//case 2:
	//	type = 2;
	//	break;
	//case 3:
	//	type = 3;
	//	break;
	//case 4:
	//	type = 4;
	//	break;
	//case 5:
	//	type = 5;
	//	break;
	//case 6:
	//	type = 6;
	//	break;
	//case 7:
	//	type = 7;
	//	break;
	//case 8:
	//	type = 8;
	//	break;
	//}
	PlayerOverlay->SetImage(type);
}
void ACCharacterPlayer::update()
{
	//curState->update(*this);
	if (!IsValid(GetWorld()) || GetWorld()->bIsTearingDown)
		return;
	curState->UpdateStates();

	//FVector inputVector = GetLastMovementInputVector();
	//float magnitude = inputVector.Size();

	//if (inputVector.X < 0.0f) {
	//	UE_LOG(LogTemp, Warning, TEXT("Left"));// 왼쪽으로 이동
	//	if (magnitude > 0.0f) {
	//		// 이동 거리 확인
	//	}
	//}
	//else if (inputVector.X > 0.0f) {
	//	// 오른쪽으로 이동
	//	UE_LOG(LogTemp, Warning, TEXT("Right"));
	//	if (magnitude > 0.0f) {
	//		// 이동 거리 확인
	//	}
	//}
	//if (inputVector.Y < 0.0f) {
	//	UE_LOG(LogTemp, Warning, TEXT("Forward"));// 왼쪽으로 이동
	//	if (magnitude > 0.0f) {
	//		// 이동 거리 확인
	//	}
	//}
	//else if (inputVector.Y > 0.0f) {
	//	// 오른쪽으로 이동
	//	UE_LOG(LogTemp, Warning, TEXT("backward"));
	//	if (magnitude > 0.0f) {
	//		// 이동 거리 확인
	//	}
	//}
	////if (Cast<US_IDLE_NEW>(curState))
	//if (Cast<AS_IDLE_A>(curState.GetObject()))
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("IS_AS_IDLE"));
	//}
}
void ACCharacterPlayer::updateInput()
{
	//UPlayerStateBase* state = curState->updateInput(*this);
	//if (state != NULL)
	//{
	//	curState->exit(*this);
	//	curState->Destroy();
	//	curState = state;
	//	curState->enter(*this);
	//}
}

void ACCharacterPlayer::Move(const FInputActionValue& Value)
{

	FVector2D MovementVector = Value.Get<FVector2D>();


	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);


	AddMovementInput(ForwardDirection, MovementVector.X*moveSpeed);
	AddMovementInput(RightDirection, MovementVector.Y * moveSpeed);
	
}

void ACCharacterPlayer::QuickRotate(const FInputActionValue& Value)
{

	FVector2D MovementVector = Value.Get<FVector2D>();


	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);


	AddMovementInput(ForwardDirection, MovementVector.X * moveSpeed);
	AddMovementInput(RightDirection, MovementVector.Y * moveSpeed);

}

void ACCharacterPlayer::StopMove()
{
	AddMovementInput(FVector::ZeroVector, 0.0f);
}

void ACCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();



	// 현재 컨트롤러의 회전 값을 가져옵니다.
	FRotator CurrentRotation = Controller->GetControlRotation();
	float CurrentPitch = CurrentRotation.Pitch;

	// 피치 각도를 제한합니다.
	float MinPitch = 10.0f; // 위쪽으로 40도 제한
	float MaxPitch = 330.0f;  // 아래쪽으로 40도 제한

	// 새로운 피치 각도를 계산합니다.
	//float NewPitch = FMath::Clamp(FMath::UnwindDegrees(CurrentPitch + LookAxisVector.Y), MinPitch, MaxPitch);
	//float NewPitch = FMath::Clamp(CurrentPitch + LookAxisVector.Y, MinPitch, MaxPitch);
	float NewPitch = CurrentPitch + LookAxisVector.Y;

	if (NewPitch > 10.0f && 330 > NewPitch)
	{
		float distance1 = FMath::Abs(10.0f - NewPitch);
		float distance2 = FMath::Abs(330.0f - NewPitch);

		if (distance1 > distance2)
		{
			NewPitch = 330.0f;
		}
		else
		{
			NewPitch = 10.0f;
		}
	}

	CurrentRotation.Pitch = NewPitch;
	//// 제한된 피치 각도를 적용합니다.

	Controller->SetControlRotation(CurrentRotation);//전체 회전 변경
	//UE_LOG(LogTemp, Warning, TEXT("LookAxisVector.Y : %f"), NewPitch);

	////AddControllerPitchInput(LookAxisVector.Y);
	//UE_LOG(LogTemp, Warning, TEXT("ControllRotation.Y : %f\n"), CurrentRotation.Pitch);
	//AddControllerPitchInput(CurrentPitch); inputaction으로는 바뀌는 값을 더해주는식으로 하는것이기에 이렇게 하면 안된다.
	AddControllerYawInput(LookAxisVector.X);	
}

void ACCharacterPlayer::Draw()
{
		NoAnimDraw();
		PlayAnimMontage(AM_Draw);
}

void ACCharacterPlayer::NoAnimDraw()
{
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("S_Draw"));
}

void ACCharacterPlayer::Sheath()
{
	NoAnimSheath();
	PlayAnimMontage(AM_Sheath);
}

void ACCharacterPlayer::NoAnimSheath()
{
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("S_Sheath"));
}

void ACCharacterPlayer::GetHit_Implementation(const FVector& ImpactPoint, AActor* Offense)
{
	if (bIsParring)//패링시에 상태 설정해줌
	{
		UPARRING_O* state = Cast<UPARRING_O>(curState->GetSubState());
		if (state != NULL)
		{
			curState->GetSubState()->SwitchState(stateFactory->CreatePARRINGSUCCESS());//서브 상태에서 바꾸는 것이기에 이렇게 사용해야함.
			return;
		}
	}
	if (Cast<USUPERARMOR_O>(curState))
	{
		UGameplayStatics::PlaySound2D(this, HittedSound, 1, 1, 0.3);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HittedParticle, ImpactPoint);
		return;
	}
	if (Cast<UINVINCIBILITY_O>(curState))
		return;
	if (Cast<UHIT_O>(curState))
		return;
	curState->SwitchState(stateFactory->CreateHIT());
	UKNOCKBACK_O* temp = Cast<UKNOCKBACK_O>(curState->GetSubState());
	if (temp)
	{
		UGameplayStatics::PlaySound2D(this, HittedSound,1,1,0.3);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HittedParticle, ImpactPoint);
		temp->SetPoint(Offense->GetTransform().GetLocation());
		temp->Start();
	}

}

float ACCharacterPlayer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Cast<UNORMAL_O>(curState)|| Cast<USUPERARMOR_O>(curState))
	{
		Attributes->ReceiveDamage(Damage);
		if (Attributes->IsAlive())
			PlayerOverlay->SetPlayerHPImage(Attributes->GetCurHp() / 20);
			//PlayerOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
		else
		{
			PlayerOverlay->SetHealthBarPercent(0);
			bIsDie = true;
			//Restart->SetVisibility(ESlateVisibility::Visible);
			Restart->AddToViewport();
			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus(Restart->GetCachedWidget());
			getPlayerController()->SetInputMode(InputMode);
			getPlayerController()->SetShowMouseCursor(true);
			PlayerOverlay->SetPlayerHPImage(-1);
			SetRagdollPhysics();
		}
	}
	return Damage;
}
void ACCharacterPlayer::SetRagdollPhysics()
{
	bool bInRagdoll;
	USkeletalMeshComponent* Mesh3P = GetMesh();

	if (!IsValid(this))
	{
		bInRagdoll = false;
	}
	else if (!Mesh3P || !Mesh3P->GetPhysicsAsset())
	{
		bInRagdoll = false;
	}
	else
	{
		Mesh3P->SetAllBodiesSimulatePhysics(true);
		Mesh3P->SetSimulatePhysics(true);
		Mesh3P->WakeAllRigidBodies();
		Mesh3P->bBlendPhysics = true;

		bInRagdoll = true;
	}

	UCharacterMovementComponent* CharacterComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (CharacterComp)
	{
		CharacterComp->StopMovementImmediately();
		CharacterComp->DisableMovement();
		CharacterComp->SetComponentTickEnabled(false);
	}

	if (!bInRagdoll)
	{
		// Immediately hide the pawn
		TurnOff();
		SetActorHiddenInGame(true);
		SetLifeSpan(5.f);
	}
	else
	{
		SetLifeSpan(5.f);
	}
}


UPlayerOverlay* ACCharacterPlayer::GetHUD()
{
	return PlayerOverlay;
}

bool ACCharacterPlayer::HasEnoughStamina(float Cost)
{
	return Attributes->GetStaminaPercent() > (Cost/Attributes->GetMaxStamina());
}

void ACCharacterPlayer::EnemyDie()
{
	PlayerOverlay->CheckClearCondition();
}



void ACCharacterPlayer::AttackCheck()
{
	//if (!bWantCombo)
		return;
	bIsCombo = true;
	WaitFrame = 70;
}


void ACCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// InputAction과 InputMappingContext를 연결
	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	FString mapName = GetWorld()->GetMapName();
	FString SmapName = FPackageName::GetShortName(mapName);
	FString clearmap = "GuardianAI";

	InitializePlayerOverlay();

	if (mapName.Contains(clearmap))
	{
		return;
	}
	EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Triggered, InventoryWidget, &UInventoryComponent::ShowInventory);
	//EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Triggered, InventoryWidget, &UInventoryComponent::InteractionKeyDown);
	//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACCharacterPlayer::Jump);
	//EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	//기본 움직임 가능

	

	//EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ACCharacterPlayer::Move);
	//EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACCharacterPlayer::Look);

	//EnhancedInputComponent->BindAction(DrawAction, ETriggerEvent::Triggered, this, &ACCharacterPlayer::Draw);
	//EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Triggered, this, &ACCharacterPlayer::Draw);
	//
	//EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &ACCharacterPlayer::Run);
	///*EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ACCharacterPlayer::GoWalk);
	//EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Canceled, this, &ACCharacterPlayer::GoWalk);*/
	//트리거가 들어갔을때 아닐때를 인식해서 사용함

	//EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ACCharacterPlayer::Walk);
	//EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Completed, this, &ACCharacterPlayer::GoIdle);


	//EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ACCharacterPlayer::DoAttack);
	//EnhancedInputComponent->bBlockInput = true;
	//밑에 적의 컨트롤러를 달고 있다면 해당하는 키의 작동이 일어나지 않는다.
}





