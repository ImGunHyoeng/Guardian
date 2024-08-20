// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/GuardianEnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/OFSMCollection.h"
#include "Components/AttributeComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/HealthBarComponent.h"

// Sets default values
AGuardianEnemyBase::AGuardianEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	//Body = CreateDefaultSubobject<UCapsuleComponent>("Body");
	//Body->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	//Body->SetupAttachment(GetRootComponent());

	//Bone = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	//Bone->SetupAttachment(Body);
	
	AttackStartRange = CreateDefaultSubobject<USphereComponent>("AttackStartRange");
	AttackEndRange = CreateDefaultSubobject<USphereComponent>("AttackEndRange");

	DetectRange = CreateDefaultSubobject<USphereComponent>("DetectRange");

	AttackStartRange->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AttackStartRange->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	AttackEndRange->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AttackEndRange->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	DetectRange->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	DetectRange->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	AttackStartRange->SetupAttachment(GetMesh());
	AttackEndRange->SetupAttachment(GetMesh());
	DetectRange->SetupAttachment(GetMesh());
	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attribute"));
	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGuardianEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
	HealthBarWidget->SetVisibility(false);
}

float AGuardianEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void AGuardianEnemyBase::GetHit_Implementation(const FVector& ImpactPoint, AActor* Offense)
{
	//DrawDebugSphere(GetWorld(), ImpactPoint, 20, 32, FColor::Red, true);
	ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(Offense->GetOwner());
	if (Player)
	{
		if (Cast<UINVINCIBILITY_O>(Player->GetCurPlayerState()))//패링성공시에 공격을 나타냄.
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParringParticle, ImpactPoint);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), ThunderSound, ImpactPoint);
			return;
		}
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HittedParticle, ImpactPoint);
	}
}

// Called every frame
void AGuardianEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGuardianEnemyBase::HitReact(const FVector& ImpactPoint)
{
}

void AGuardianEnemyBase::DeadReact(const FVector& ImpactPoint)
{
}

void AGuardianEnemyBase::SetWidgetVisible(bool input)
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(input);
	}
}

// Called to bind functionality to input
void AGuardianEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

