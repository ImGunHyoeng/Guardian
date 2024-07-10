// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSM/PlayerStateBase.h"
#include "ATTACK_O.generated.h"


UENUM()
enum class EAttackState :uint8
{
	END
	, DONE
	, DOING
};
class ACCharacterPlayer;
class UPlayerStateFactory;
UCLASS()
class CAIMAN_API UATTACK_O : public UPlayerStateBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	UATTACK_O();

	//virtual IIPlayerState* updateInput(class ACCharacterPlayer& player);
	virtual void updateInput() override;
	virtual void update() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void Destroy() override;
	virtual void InitializeSubState() override;

	UFUNCTION(BlueprintCallable)
	void AttackStateEnd() { curAttackState = EAttackState::END; }
	UFUNCTION(BlueprintCallable)
	void AttackStateDone() { curAttackState = EAttackState::DONE; }
	UFUNCTION(BlueprintCallable)
	void AttackStateDoing() { curAttackState = EAttackState::DOING; }
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAttackState curAttackState;

	void ChangeChargeAttack();


	int DoingTime;
	bool keepPress;
private:
	bool changeCharge;
};
