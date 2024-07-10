// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSM/PlayerStateBase.h"
#include "S_ROLL_O.generated.h"

/**
 * 
 */
UCLASS()
class CAIMAN_API US_ROLL_O : public UPlayerStateBase
{
	GENERATED_BODY()	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isRoll;
	bool end;
	//virtual IIPlayerState* updateInput(class ACCharacterPlayer& player);
	virtual void updateInput() override;
	virtual void update() override;
	virtual void enter() override;
	virtual void exit() override;
	virtual void Destroy() override;
	virtual void InitializeSubState() override;
	class UKwangAnimInstance* kwang;
	US_ROLL_O(){ isRoll = true; }
	
	FName input;
	//~S_WALK() { UE_LOG(LogTemp, Warning, TEXT("Walk Destroy")); }
};
