// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/KwangAnimInstance.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "CCharacterPlayer.h"
#include "Kismet/KismetMathLibrary.h"

void UKwangAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	Player = Cast<ACCharacterPlayer>(TryGetPawnOwner());
	if (Player)
	{
		PlayerMovement = Player->GetCharacterMovement();
	}
}

void UKwangAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (Player)
	{
		Waitframe=Player->GetWaitFrame();
		
	}
	if (PlayerMovement)
	{
		Velocity = UKismetMathLibrary::VSizeXY(PlayerMovement->Velocity);
		MaxSpeed = PlayerMovement->GetMaxSpeed();
		IsFalling=PlayerMovement->IsFalling();
	}
}
