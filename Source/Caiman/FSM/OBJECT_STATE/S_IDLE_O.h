// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSM/PlayerStateBase.h"
#include "S_IDLE_O.generated.h"

/**
 * 
 */
class ACCharacterPlayer;
class UPlayerStateFactory;
UCLASS()
class CAIMAN_API US_IDLE_O : public UPlayerStateBase
{
	GENERATED_BODY()
public:
	US_IDLE_O() {};
	virtual void updateInput() override;
	virtual void update() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void Destroy() override;
	virtual void InitializeSubState() override;
	class UKwangAnimInstance* kwang;
};
