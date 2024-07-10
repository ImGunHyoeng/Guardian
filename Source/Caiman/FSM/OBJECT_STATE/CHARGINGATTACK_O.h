// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FSM/PlayerStateBase.h"
#include "CHARGINGATTACK_O.generated.h"

/**
 * 
 */
UENUM()
enum class EChargeAttackState :uint8
{
	STAY
	, START
	, DOING
	, DONE
};
UCLASS()
class CAIMAN_API UCHARGINGATTACK_O : public UPlayerStateBase
{
	GENERATED_BODY()
public:
	virtual void updateInput() override;
	virtual void update() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void Destroy() override;
	virtual void InitializeSubState() override;
	UPROPERTY(BlueprintReadWrite)
	EChargeAttackState curstate;
	UAnimInstance* instance;
	float DoingTime;
	const float standardDoing = 2;
	UPROPERTY(BlueprintReadOnly)
	float resultWaitTime;
	float WaitTime;
	const float ExtraTimeLimit = 4;
	UPROPERTY(BlueprintReadWrite)
	bool changeState;
	UFUNCTION(BlueprintCallable)
	void ChangeDoing(class ACCharacterPlayer* player);
};
