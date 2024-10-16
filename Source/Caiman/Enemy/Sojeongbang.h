// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/GuardianEnemyBase.h"
#include "CCharacterPlayer.h"
#include "Sojeongbang.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FStandardDelegateSignature)
DECLARE_DELEGATE_OneParam(FParamDelegateSignature,bool)
UCLASS()
class CAIMAN_API ASojeongbang : public AGuardianEnemyBase
{
	GENERATED_BODY()
public:
	FStandardDelegateSignature MyStandardDelegate;
	FParamDelegateSignature MyParamDelegate;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void HitReact(const FVector& ImpactPoint);
	virtual void DeadReact(const FVector& ImpactPoint);
	UPROPERTY()
	ACCharacterPlayer* player;
	UFUNCTION(BlueprintCallable)
	void Excute(bool condition);

	UFUNCTION(BlueprintImplementableEvent)//블루프린트 호출 함수
	void Clear(ACCharacterPlayer *Input);
};
