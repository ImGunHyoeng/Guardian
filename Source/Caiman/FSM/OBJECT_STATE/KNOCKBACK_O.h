// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FSM/PlayerStateBase.h"
#include "KNOCKBACK_O.generated.h"

/**
 * 
 */
UCLASS()
class CAIMAN_API UKNOCKBACK_O : public UPlayerStateBase
{
	GENERATED_BODY()
public:
	UKNOCKBACK_O();
	virtual void updateInput() override;
	virtual void update() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void Destroy() override;
	virtual void InitializeSubState() override;
	bool end;
	bool can;
	FVector ParticlePoint;
	void SetPoint(const FVector& ImpactPoint);
	void Start();
};
