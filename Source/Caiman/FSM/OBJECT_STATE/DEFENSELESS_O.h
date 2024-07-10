// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FSM/PlayerStateBase.h"
#include "DEFENSELESS_O.generated.h"

/**
 * 
 */
UCLASS()
class CAIMAN_API UDEFENSELESS_O : public UPlayerStateBase
{
	GENERATED_BODY()

public:
	virtual void updateInput() override;
	virtual void update() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void Destroy() override;
	virtual void InitializeSubState() override;
	class UKwangAnimInstance* kwang;

};
