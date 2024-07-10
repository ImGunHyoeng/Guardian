// Fill out your copyright notice in the Description page of Project Settings.


#include "CMonsterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AttributeComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/HealthBarComponent.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/OFSMCollection.h"
#include "HUD/MenuWidget.h"

// Sets default values

ACMonsterBase::ACMonsterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;//컨트롤러의 회전을 따라갈 것인지를 정하는 것
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;


	//SkelatalMesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));//메시가 항상 위쪽에 90정도 띄어있기에  -90으로 위치를 맞추고 캐릭터와 방향이 -90정도로 화살표가 돌아가 있기에 이를 조절함.

	//Capsule
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CCapsule"));

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));//충돌 설정시에 profile의 이름을 설정하는 것.

	//CharacterMovement
	GetCharacterMovement()->bOrientRotationToMovement = true;//원하는 방향으로 캐릭터가 움직이는 것
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.f, 0.0f);//y축으로의 회전만 넣어서 Yaw회전을 기준으로 움직이도록 한 것이다.
	GetCharacterMovement()->JumpZVelocity = 500.0f;//점프력 설정
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;//걷는 최대 속도
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;//걷기 완화 속도
	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attribute"));
	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));

	HealthBarWidget->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACMonsterBase::BeginPlay()
{
	Super::BeginPlay();
	hp = 100;
	//Clear= CreateWidget<UMenuWidget>(GetWorld(), ClearClass);
	bIsLive = true;
	bIsAlredyDie = false;
	bIsAttacking = false;
	bIsGoHome = false;
	bIsDetect = false;
	bIsAttacked = false;
	bIsCoolTime = false;
	bIsHeal = false;
	bIsInC_AttackRange = false;
	bIsInD_Range = false;
	bIsInL_AttackRange = false;
	bIsRunAwayDone = false;
	attackType = 0;
	healcount = 0;
	HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
	HealthBarWidget->SetVisibility(false);
	//Clear = CreateDefaultSubobject<UMenuWidget>(TEXT("Clear"));
}

void ACMonsterBase::setHp(float _hp)
{
	if (Attributes)
	{
		Attributes->ReceiveDamage(_hp*-1);
		HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
	}
	
}

void ACMonsterBase::SetWidgetVisible(bool input)
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(input);
	}
}

// Called every frame
void ACMonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Monster HP:%f"),hp);
}

float ACMonsterBase::getHp()
{
	if (Attributes)
	{
		return Attributes->GetHealthPercent();
	}
	return 0;
}

// Called to bind functionality to input
void ACMonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

void ACMonsterBase::GetHit_Implementation(const FVector& ImpactPoint, AActor* Offense)
{
	//DrawDebugSphere(GetWorld(), ImpactPoint, 20, 32, FColor::Red, true);
	ACCharacterPlayer *Player=Cast<ACCharacterPlayer>(Offense->GetOwner());
	if (Player)
	{
		if (Cast<UINVINCIBILITY_O>(Player->GetCurPlayerState()))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParringParticle, ImpactPoint);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ThunderSound, ImpactPoint);
			return;
		}
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HittedParticle, ImpactPoint);
	}
}


float ACMonsterBase::InternalTakePointDamage(float Damage, FPointDamageEvent const& PointDamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage=Super::InternalTakePointDamage(Damage, PointDamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("%s and damage %f"), TEXT("Damaged_enemy"),damage);
	if (bIsAlredyDie)
		return damage;
	UAnimMontage* animSelction=nullptr;
	Attributes->ReceiveDamage(damage);
	bIsLive = Attributes->IsAlive();
	HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
	animSelction = bIsLive ? AM_Hited : AM_Dead;
	PlayAnimMontage(animSelction);
	
	if (bIsHeal)
	{
		if (bIsRunAwayDone)
		{
			bIsHeal = false;
			healcount++;
			StopAnimMontage();
			PlayAnimMontage(AM_Angry);
		}
	}

	if (!bIsLive)
	{
		if (!bIsAlredyDie)
		{
			HealthBarWidget->SetVisibility(false);
			//Clear->SetVisibility(ESlateVisibility::Visible);
			Cast<ACCharacterPlayer>(DamageCauser->GetOwner())->EnemyDie();
			//Clear->AddToViewport();
			bIsAlredyDie = true;
			SetLifeSpan(5.0f);
		}
	}


	return damage;
}

float ACMonsterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	UE_LOG(LogClass, Warning, TEXT("Damage : %f"), Damage);
	return Damage;
	// 여기에서는 데미지가 잘 안들어오는 오류가 있는건지 아닌지 모르겠음
}
//
//void ACMonsterBase::ReceivePointDamage(float Damage, const UDamageType* DamageType, FVector HitLocation, FVector HitNormal, UPrimitiveComponent* HitComponent, FName BoneName, FVector ShotFromDirection, AController* InstigatedBy, AActor* DamageCauser)
//{
//	UE_LOG(LogTemp, Warning, TEXT("%s"), "Damaged_enemy");
//
//}

