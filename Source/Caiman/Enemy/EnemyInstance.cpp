// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyInstance.h"
#include "Enemy/AnimalBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/PawnMovementComponent.h"

void UEnemyInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	Enemy = Cast<AAnimalBase>(TryGetPawnOwner());
	if (Enemy)
	{
		EnemyMovement = Enemy->GetMovementComponent();
	}
}

void UEnemyInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (EnemyMovement)
	{
		Velocity = UKismetMathLibrary::VSizeXY(EnemyMovement->Velocity);
		MaxSpeed = EnemyMovement->GetMaxSpeed();
		
	}
}
