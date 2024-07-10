// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AnimalBase.h"
#include "Components/CapsuleComponent.h"
#include "CCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/App.h"
#include "Enemy/EnemyInstance.h"
#include "Components/AttributeComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/HealthBarComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Item/ItemBase.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AAnimalBase::AAnimalBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	Body = CreateDefaultSubobject<UCapsuleComponent>("Body");
	Body->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Body->SetupAttachment(GetRootComponent());

	Bone = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	Bone->SetupAttachment(Body);
	
	FleeStartRange = CreateDefaultSubobject<USphereComponent>("FleeStart");
	FleeEndRange = CreateDefaultSubobject<USphereComponent>("FleeEnd");
	
	FleeStartRange->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	FleeStartRange->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
	FleeEndRange->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	FleeEndRange->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	FleeStartRange->SetupAttachment(Body);
	FleeEndRange->SetupAttachment(Body);
	//DetectEndRange = CreateDefaultSubobject<USphereComponent>("DetectEnd");
	//DetectStartRange= CreateDefaultSubobject<USphereComponent>("DetectStart");
	//AttackStatrRange = CreateDefaultSubobject<USphereComponent>("AttackStart");
	//AttackEndRange = CreateDefaultSubobject<USphereComponent>("AttackEnd");
	
	//DetectEndRange->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//DetectEndRange->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	//DetectStartRange->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//DetectStartRange->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	//AttackEndRange->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//AttackEndRange->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	//AttackStatrRange->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//AttackStatrRange->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	//DetectEndRange->SetupAttachment(Bone);
	//DetectStartRange->SetupAttachment(Bone);
	//AttackEndRange->SetupAttachment(Bone);
	//AttackStatrRange->SetupAttachment(Bone);


	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attribute"));
	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(RootComponent);
	Curstate = EAnimalState::STROLL;
}

// Called when the game starts or when spawned
void AAnimalBase::BeginPlay()
{
	Super::BeginPlay();
	//충돌처리하는 것과 엮어주는 기능


	FleeStartRange->OnComponentBeginOverlap.AddDynamic(this, &AAnimalBase::FLEEInRange);
	FleeEndRange->OnComponentEndOverlap.AddDynamic(this, &AAnimalBase::FLEEOutRange);
	//AttackStatrRange->OnComponentBeginOverlap.AddDynamic(this, &AAnimalBase::InAttackRange);

	targetSet = false;
	spawnpoint = GetActorLocation();
	//enemyaniminstance = Cast<UEnemyInstance>(Bone->GetAnimInstance());
	/*FVector ForwardVector = GetActorForwardVector();
	FRotator Rotation = FRotator(0, 0, 90);
	ForwardVector = ForwardVector.RotateVector(Rotation);*/
	predirection = FVector(0, 0, 0);
	//RotationSpeed = 0.5;
	//targetLocation = GetActorLocation() + FMath::VRand() * 200;
	//targetSet = true;
	HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
	animInstance = Bone->GetAnimInstance();
	moveSpeed = 1;
	HealthBarWidget->SetVisibility(false);
}

//void AAnimalBase::InAttackRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//
//	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, FString("ATTACKRANGE_IN"));
//	ACCharacterPlayer* target = Cast<ACCharacterPlayer>(OtherActor);
//	if (target)
//	{
//		enemyaniminstance->setIsMoveTowardsPlayerEnd();
//		enemyaniminstance->setIsAttack();
//		Curstate = EAnimalState::ATTACK;
//		AttackEndRange->OnComponentEndOverlap.AddDynamic(this, &AAnimalBase::OutAttackRange);
//		AttackStatrRange->OnComponentBeginOverlap.Remove(this, FName("InAttackRange"));
//
//	}
//}

//void AAnimalBase::OutAttackRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, FString("ATTACKRANGE_OUT"));
//	ACCharacterPlayer* target = Cast<ACCharacterPlayer>(OtherActor);
//	if (target)
//	{
//		enemyaniminstance->setIsMoveTowardsPlayer();
//		enemyaniminstance->setIsAttackEnd();
//		Curstate = EAnimalState::MOVETOWARDPLAYER;
//		AttackEndRange->OnComponentEndOverlap.Remove(this, FName("OutAttackRange"));
//
//		AttackStatrRange->OnComponentBeginOverlap.AddDynamic(this, &AAnimalBase::InAttackRange);
//
//
//	}
//}

//void AAnimalBase::PlayerOutRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, FString("DETECT_OUT"));
//	ACCharacterPlayer* target = Cast<ACCharacterPlayer>(OtherActor);
//	if (target)
//	{
//		//Curstate = EAnimalState::STROLL;
//		Curstate = EAnimalState::STROLL;
//		player = nullptr;
//
//		enemyaniminstance->setIsMoveTowardsPlayerEnd();
//		enemyaniminstance->setStroll();
//		DetectStartRange->OnComponentBeginOverlap.AddDynamic(this, &AAnimalBase::PlayerInRange);
//		DetectEndRange->OnComponentEndOverlap.Remove(this, FName("PlayerOutRange"));
//	}
//}

//void AAnimalBase::PlayerInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, FString("DETECT_IN"));
//	ACCharacterPlayer* target = Cast<ACCharacterPlayer>(OtherActor);
//	if (target)
//	{
//		player = target;
//		targetSet = false;
//		enemyaniminstance->setIsMoveTowardsPlayer();
//		enemyaniminstance->setStrollEnd();
//		Curstate = EAnimalState::MOVETOWARDPLAYER;
//		DetectStartRange->OnComponentBeginOverlap.Remove(this, FName("PlayerInRange"));
//
//		DetectEndRange->OnComponentEndOverlap.AddDynamic(this, &AAnimalBase::PlayerOutRange);
//	}
//}







void AAnimalBase::FLEEInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(true);
	}

}

void AAnimalBase::FLEEOutRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}
	Curstate = EAnimalState::STROLL;
	targetSet = false;
	player = nullptr;
}

float AAnimalBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Attributes)
	{
		Attributes->ReceiveDamage(DamageAmount);
		moveSpeed = Attributes->GetHealthPercent();
		if (Attributes->GetHealthPercent() == 0)
		{
			HealthBarWidget->SetHealthPercent(0);
			Curstate = EAnimalState::DEAD;
			SpawnItem();
			Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Bone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			UFloatingPawnMovement* FloatingPawnMovement = Cast<UFloatingPawnMovement>(Bone->GetOwner()->GetComponentByClass(UFloatingPawnMovement::StaticClass()));
			if (FloatingPawnMovement)
				FloatingPawnMovement->DestroyComponent();
			SetLifeSpan(5.0f);
			HealthBarWidget->SetVisibility(false);
			
			return 0;
		}
		if (HealthBarWidget)
		{
			HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
			Curstate = EAnimalState::HITTED;
			player = Cast<ACCharacterPlayer>(EventInstigator->GetPawn());
			//노티파이로 flee상태로 전환
		}
	}
	return 0.0f;
}

// Called every frame
void AAnimalBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateInput();
	Update();

	//Bone->SetRelativeRotation(FRotator(0, 180, 0).Quaternion());



}

//FQuat AAnimalBase:: SmoothRotation(FQuat& StartRotation,  FQuat& EndRotation, float DeltaTime, float RotationSpeed)
//{
//	// 보간을 위한 시간 단계 계산
//	float T = FMath::Min(DeltaTime, 1.0f);
//
//	// 보간 계수 계산
//	float Alpha = T * RotationSpeed;
//
//	// 시작 및 끝 회전 사이 Slerp(Spherical Linear Interpolation) 수행
//	FQuat InterpolatedRotation = FQuat::Slerp(StartRotation, EndRotation, Alpha);
//
//	return InterpolatedRotation;
//}

void AAnimalBase::Update()
{
	/*if (Curstate == EAnimalState::MOVETOWARDPLAYER)
	{
		FVector PawnLocation = GetActorLocation();

		if (player)
		{
			FVector PlayerLocation = player->GetActorLocation();


			direction = PlayerLocation - PawnLocation;
			direction.Normalize();
			direction.Z = 0;


			UPawnMovementComponent* MovementComponent = Cast<UPawnMovementComponent>(GetMovementComponent());
			if (MovementComponent) {

				DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + direction * 100, FColor::Blue, false, 2.1f);
				SetActorRotation(direction.Rotation());
				DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100, FColor::Red, false, 10.f, 0, 10.0f);
				MovementComponent->AddInputVector(direction * 0.8);
			}
		}
		GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, FString("MoveTowardPlayer"));
		return;
	}*/

	if (Curstate == EAnimalState::FLEE)
	{
		//체력회복하는 것이 보이도록
		if (Attributes)
		{
			//Attributes->ReceiveDamage(-(FApp::GetDeltaTime()));
			if (HealthBarWidget)
			{
				HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
			}
		}

		//hp += FApp::GetDeltaTime() * 10;
		if (player)
		{
			direction = GetActorLocation() - player->GetActorLocation();
			direction.Z = 0;
			FVector PlayerForwardVector = player->GetActorForwardVector();

			FHitResult HitResult;
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(Bone->GetOwner());

			//DrawDebugLine(GetWorld(), GetActorLocation() + GetActorUpVector() * 20, GetActorLocation() + GetActorUpVector() * 20 + direction * 4, FColor::Blue, false, 6.f);
			if (GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation()+GetActorUpVector()*20, GetActorLocation() + GetActorUpVector() * 20 + direction * 4, ECC_Visibility, QueryParams))
			{
				targetSet = false;
				redirection_L = direction;
				redirection_R = direction;
				isredirection = false;
			}
			else
			{
				targetSet = true;
			}

			UPawnMovementComponent* MovementComponent = Cast<UPawnMovementComponent>(GetMovementComponent());
			if (MovementComponent)
			{
				if (targetSet)
				{
					//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + direction * 100, FColor::Blue, false, 2.1f);
					SetActorRotation(direction.Rotation());
					MovementComponent->AddInputVector(direction * moveSpeed);//단위벡터 값 넣어주기
				}
				else
				{
					float Yaw_L=0;
					float Yaw_R=0;
					while(!isredirection)
					{

						FTransform RotationMatrix;
						RotationMatrix.SetRotation(FRotator(0, Yaw_L, 0).Quaternion());
						redirection_L = RotationMatrix.TransformVector(redirection_L);
						RotationMatrix.SetRotation(FRotator(0, Yaw_R, 0).Quaternion());
						redirection_R = RotationMatrix.TransformVector(redirection_R);

						if (GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() + redirection_L * 4, ECC_Visibility, QueryParams))
						{
							Yaw_L++;
						}
						else
						{
							redirection = redirection_L;
							isredirection = true;
							continue;
						}
						if (GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() + redirection_R * 4, ECC_Visibility, QueryParams))
						{
							Yaw_R--;
						}
						else
						{
							redirection = redirection_R;
							isredirection = true;
							continue;
						}
					}
					SetActorRotation(redirection.Rotation());
					MovementComponent->AddInputVector(redirection * moveSpeed);//단위벡터 값 넣어주기
				}
			}
		}
		//GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, FString("FLee"));
		return;
	}

	if (Curstate == EAnimalState::STROLL)
	{
		if ((GetActorLocation() - spawnpoint).Size() > 500)//원점 복귀
		{
			targetSet = true;
			//predirection=(targetLocation - GetActorLocation()).GetSafeNormal();
			predirection = GetActorForwardVector();
			targetLocation = spawnpoint;
			targetLocation.Z = GetActorLocation().Z;
			//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100, FColor::Black, false, 10.f, 0, 10.0f);
			direction = (targetLocation - GetActorLocation()).GetSafeNormal();
			//float yaw = GetDegree(direction);

			//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100, FColor::Red, false, 10.f, 0, 10.0f);
			UE_LOG(LogTemp, Warning, TEXT("Body %f"), Body->GetComponentRotation().Yaw);
			UE_LOG(LogTemp, Warning, TEXT("Bone %f"), Bone->GetComponentRotation().Yaw);
			UE_LOG(LogTemp, Warning, TEXT("Forward %f"), GetActorForwardVector().Rotation().Yaw);

		}//너무 멀어졌다면 스폰 위치로 이동

		if (!targetSet)
		{
			predirection = GetActorForwardVector();
			//이전 벡터의 방향을 구함.
			targetLocation = GetActorLocation() + FMath::VRand() * 200;//단위벡터이기에 위치가 사용됨.
			targetLocation.Z = GetActorLocation().Z;
			direction = (targetLocation - GetActorLocation()).GetSafeNormal();
			//float yaw = GetDegree(direction);
			
			//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100, FColor::Black, false, 10.f, 0, 10.0f);

			//RootComponent->SetWorldRotation((FRotator(0, yaw, 0)));
			targetSet = true;

			UE_LOG(LogTemp, Warning, TEXT("Body %f"), Body->GetComponentRotation().Yaw);
			UE_LOG(LogTemp, Warning, TEXT("Bone %f"), Bone->GetComponentRotation().Yaw);
			UE_LOG(LogTemp, Warning, TEXT("Forward %f"), GetActorForwardVector().Rotation().Yaw);

		}
		if ((FVector(GetActorLocation().X, GetActorLocation().Y, 0) - FVector(targetLocation.X, targetLocation.Y, 0)).Size() <= 20)
		{
			//sumDeltaTime = 0;
			targetSet = false;
			return;
		}
		targetLocation.Z = GetActorLocation().Z;
		UPawnMovementComponent* MovementComponent = Cast<UPawnMovementComponent>(GetMovementComponent());
		if (MovementComponent)
		{
			SetActorRotation(FMath::RInterpTo(GetActorForwardVector().Rotation(), direction.Rotation(), FApp::GetDeltaTime(), RotationSpeed));
			FHitResult HitResult;
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(this);

			if (GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() + direction * 4, ECC_Visibility, QueryParams))
			{
				targetSet = false;
			}
			MovementComponent->AddInputVector(direction * 0.5f);//단위벡터 값 넣어주기

			//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100, FColor::Red, false, 10.f, 0, 10.0f);
			//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + direction * 100, FColor::Blue, false, 2.1f, 0, 15);
		}




		//GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, FString("Stroll"));
		return;
	}

	//if (Curstate == EAnimalState::ATTACK)
	//{
	//	GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Red, FString("Attack"));
	//	//hp--;
	//	return;
	//}

}

void AAnimalBase::UpdateInput()
{
	//if (Curstate == EAnimalState::MOVETOWARDPLAYER)
	//{
	//	//if ((GetActorLocation() - player->GetActorLocation()).Size() >= 900)
	//	//{
	//	//	Curstate = EAnimalState::STROLL;
	//	//	player = nullptr;

	//	//	enemyaniminstance->setIsMoveTowardsPlayerEnd();
	//	//	enemyaniminstance->setStroll();
	//	//	return;
	//	//}
	//}
	if (Curstate == EAnimalState::FLEE)
	{
		//if (Attributes->GetHealthPercent() >= 0.6f)
		//{
		//	//DetectStartRange->OnComponentBeginOverlap.AddDynamic(this, &AAnimalBase::PlayerInRange);

		//	//AttackStatrRange->OnComponentBeginOverlap.AddDynamic(this, &AAnimalBase::InAttackRange);
		//	Curstate = EAnimalState::STROLL;
		//	targetSet = false;
		//	player = nullptr;
		//	//enemyaniminstance->setIsFleeEnd();
		//	//enemyaniminstance->setStroll();
		//	return;
		//}
	}
	if (Curstate == EAnimalState::STROLL)
	{

	}
	//if (Curstate == EAnimalState::ATTACK)
	//{
	//	if (Attributes->GetHealthPercent() <= 0.3f)
	//	{
	//		AttackStatrRange->OnComponentBeginOverlap.Remove(this, FName("InAttackRange"));
	//		DetectStartRange->OnComponentBeginOverlap.Remove(this, FName("PlayerInRange"));
	//		DetectEndRange->OnComponentEndOverlap.Remove(this, FName("PlayerOutRange"));
	//		AttackEndRange->OnComponentEndOverlap.Remove(this, FName("OutAttackRange"));
	//		enemyaniminstance->setIsFlee();
	//		enemyaniminstance->setIsAttackEnd();
	//		Curstate = EAnimalState::FLEE;
	//		return;
	//	}
	//	//if ((GetActorLocation() - player->GetActorLocation()).Size() >= 400)
	//	//{
	//	//	enemyaniminstance->setIsMoveTowardsPlayer();
	//	//	enemyaniminstance->setIsAttackEnd();
	//	//	Curstate = EAnimalState::MOVETOWARDPLAYER;
	//	//	return;
	//	//}
	//}

}

	// Called to bind functionality to input
void AAnimalBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAnimalBase::GetDegree(FVector dir)
{
	FVector actornotz = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	//float dot = FVector::DotProduct(actornotz + GetActorForwardVector(), dir+actornotz);//내적
	float cos = FVector::DotProduct( GetActorForwardVector(), dir );//내적
	float seta = acos(cos);
	FVector cross= FVector::CrossProduct( GetActorForwardVector(), dir);//외적
	float result = FMath::RadiansToDegrees(seta);
	if (cross.Z < 0)
	{
		result*=-1;//반대였다
	}
	UE_LOG(LogTemp, Warning, TEXT("FORWARD AND DIR RADIAN %f"), result);
	return result;
}

void AAnimalBase::GetHit_Implementation(const FVector& ImpactPoint, AActor* Offense)
{
	//DrawDebugSphere(GetWorld(), ImpactPoint, 20, 32, FColor::Red, true);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HittedParticle, ImpactPoint);
	//hp -= 10;
	if (Attributes->IsAlive())
		HitReact(Offense->GetTransform().GetLocation());
	else
		DeadReact(Offense->GetTransform().GetLocation());

	//PlayAnimMontage(AM_Hitted, 1, Section);
}

void AAnimalBase::SpawnItem()
{
	int value = FMath::RandRange(0, 3);
	FRotator rotator;
	GetWorld()->SpawnActor<AItemBase>(Items[value], GetActorLocation()+(0,0,20), rotator);
}

void AAnimalBase::HitReact(const FVector& ImpactPoint)
{
	FVector forward = GetActorForwardVector();
	FVector hitno_z = FVector(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	FVector toHit = (hitno_z - GetActorLocation()).GetSafeNormal();
	float cos = FVector::DotProduct(forward, toHit);
	float seta = acos(cos);
	float degree = FMath::RadiansToDegrees(seta);
	FVector Cross = FVector::CrossProduct(forward, toHit);
	if (Cross.Z < 0)
		degree *= -1;
	//UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + forward * 50, 5, FColor::Red, 15);
	//UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + toHit * 50, 5, FColor::Green, 15);
	//UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + Cross * 50, 5, FColor::Blue, 15);
	FName Section("Back");

	if (degree >= -45.f && degree < 45.f)
	{
		Section = FName("Foward");
	}
	else if (degree >= -135.f && degree < -45.f)
	{
		Section = FName("Left");
	}
	else if (degree >= 45.f && degree < 135.f)
	{
		Section = FName("Right");
	}
	
	animInstance->Montage_Play(AM_HitReact);
	//animInstance->Montage_JumpToSection(Section);
}
void AAnimalBase::DeadReact(const FVector& ImpactPoint)
{
	FVector forward = GetActorForwardVector();
	FVector hitno_z = FVector(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	FVector toHit = (hitno_z - GetActorLocation()).GetSafeNormal();
	float cos = FVector::DotProduct(forward, toHit);
	float seta = acos(cos);
	float degree = FMath::RadiansToDegrees(seta);
	FVector Cross = FVector::CrossProduct(forward, toHit);
	if (Cross.Z < 0)
		degree *= -1;
	//UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + forward * 50, 5, FColor::Red, 15);
	//UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + toHit * 50, 5, FColor::Green, 15);
	//UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + Cross * 50, 5, FColor::Blue, 15);
	FName Section("Back");

	if (degree >= -45.f && degree < 45.f)
	{
		Section = FName("Foward");
	}
	else if (degree >= -135.f && degree < -45.f)
	{
		Section = FName("Left");
	}
	else if (degree >= 45.f && degree < 135.f)
	{
		Section = FName("Right");
	}
	animInstance->Montage_Play(AM_DeadReact);
	animInstance->Montage_JumpToSection(Section);

}
