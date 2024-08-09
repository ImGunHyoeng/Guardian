// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/GuardianEnemyBase.h"

// Sets default values
AGuardianEnemyBase::AGuardianEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGuardianEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

float AGuardianEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
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

// Called to bind functionality to input
void AGuardianEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

