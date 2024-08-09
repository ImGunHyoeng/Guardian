// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/GuardianEnemyBase.h"
#include "Soldier.generated.h"

/**
 * 
 */
UCLASS()
class CAIMAN_API ASoldier : public AGuardianEnemyBase
{
	GENERATED_BODY()
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
