// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSM/OBJECT_STATE/CHARGINGATTACK_O.h"
#include "SUPERCHARGINGATTACK_O.generated.h"

/**
 * 
 */
UCLASS()
class CAIMAN_API USUPERCHARGINGATTACK_O : public UCHARGINGATTACK_O
{
	GENERATED_BODY()
	virtual void updateInput() override;
	virtual void update() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void Destroy() override;
	virtual void InitializeSubState() override;
};
