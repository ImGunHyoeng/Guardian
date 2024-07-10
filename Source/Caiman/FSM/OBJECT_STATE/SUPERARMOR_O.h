// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSM/PlayerStateBase.h"
#include "SUPERARMOR_O.generated.h"

/**
 * 
 */
UCLASS()
class CAIMAN_API USUPERARMOR_O : public UPlayerStateBase
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	USUPERARMOR_O();
	//virtual IIPlayerState* updateInput(class ACCharacterPlayer& player);
	virtual void updateInput() override;
	virtual void update() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void Destroy() override;
	virtual void InitializeSubState() override;
	bool end;
};
