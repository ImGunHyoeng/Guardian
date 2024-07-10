// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KwangAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAIMAN_API UKwangAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = Character)
	class ACCharacterPlayer* Player;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* PlayerMovement;
	UPROPERTY(BlueprintReadOnly,Category=Movement)
	bool ShouldJump;
	UPROPERTY(BlueprintReadOnly,Category=Movement)
	bool IsSwordDraw;
	UPROPERTY(BlueprintReadOnly,Category=Movement)
	bool IsJumpAttack;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float Velocity;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	int Waitframe;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float MaxSpeed;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	uint8 IsFalling:1;
	
	virtual void NativeBeginPlay();
	virtual void NativeUpdateAnimation(float DeltaTime);
	FORCEINLINE void setJump() { ShouldJump = true; }
	FORCEINLINE void setJumpEnd() { ShouldJump = false; }
	FORCEINLINE void setDraw() { IsSwordDraw = true; }
	FORCEINLINE void setSheath() { IsSwordDraw = false; }
	FORCEINLINE void setJumpAttack() { IsJumpAttack = true; }
	FORCEINLINE void setJumpAttackEnd() { IsJumpAttack = false; }
	
};
