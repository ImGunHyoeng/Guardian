// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyInstance.generated.h"

/**
 * 
 */
UCLASS()
class CAIMAN_API UEnemyInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = Character)
	class AAnimalBase* Enemy;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UPawnMovementComponent* EnemyMovement;
	//UPROPERTY(BlueprintReadOnly, Category = Movement)
	//bool ShouldJump;
	//UPROPERTY(BlueprintReadOnly, Category = Movement)
	//bool IsSwordDraw;
	//UPROPERTY(BlueprintReadOnly, Category = Movement)
	//bool IsJumpAttack;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float Velocity;

	//UPROPERTY(BlueprintReadOnly, Category = Movement)
	//int Waitframe;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float MaxSpeed;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	uint8 IsStroll : 1;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	uint8 IsMoveTowardsPlayer : 1;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	uint8 IsAttack : 1;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	uint8 IsFlee : 1;


	virtual void NativeBeginPlay();
	virtual void NativeUpdateAnimation(float DeltaTime);
	FORCEINLINE void setStroll() { IsStroll = true; }
	FORCEINLINE void setStrollEnd() { IsStroll = false; }
	FORCEINLINE void setIsMoveTowardsPlayer() { IsMoveTowardsPlayer = true; }
	FORCEINLINE void setIsMoveTowardsPlayerEnd() { IsMoveTowardsPlayer = false; }
	FORCEINLINE void setIsAttack() { IsAttack = true; }
	FORCEINLINE void setIsAttackEnd() { IsAttack = false; }
	FORCEINLINE void setIsFlee() { IsFlee = true; }
	FORCEINLINE void setIsFleeEnd() { IsFlee = false; }
};
