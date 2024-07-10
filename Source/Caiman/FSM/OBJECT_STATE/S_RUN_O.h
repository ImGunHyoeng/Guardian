// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSM/PlayerStateBase.h"
#include "S_RUN_O.generated.h"

/**
 * 
 */
UCLASS()
class CAIMAN_API US_RUN_O : public UPlayerStateBase
{
	GENERATED_BODY()
public:
	virtual void updateInput() override;
	virtual void update() override;
	virtual void enter() override;
	void RunTimerEnd();
	virtual void exit() override;
	virtual void Destroy() override;
	virtual void InitializeSubState() override;
	FTimerHandle runTimer;

};
