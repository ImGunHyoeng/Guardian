// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerStateBase.generated.h"

/**
 * 
 */
class ACCharacterPlayer;
class UPlayerStateFactory;
UCLASS()
class CAIMAN_API UPlayerStateBase : public UObject
{
	GENERATED_BODY()
public:
	//virtual IIPlayerState* updateInput(class ACCharacterPlayer& player) = 0;	
	virtual void updateInput() {};
	//virtual void update(class ACCharacterPlayer& player) = 0;
	virtual void update() {};
	virtual void enter() {};
	virtual void InitializeSubState() {};
	virtual void exit() {};
	virtual void Destroy() {};
	void UpdateStates();
	void EnterStates();
	void ExitStates();

	UPlayerStateBase();


	void SetInitalProperty(ACCharacterPlayer* _ctx, UPlayerStateFactory* _factory);

	void SetRoot(bool _input = false);

	void SwitchState(UPlayerStateBase* newState);
	UPlayerStateBase* GetSubState();
protected:
	void SetSuperState(UPlayerStateBase* newSuperState);

	void SetSubState(UPlayerStateBase* newSubState);

	ACCharacterPlayer* ctx;
	UPlayerStateFactory* factory;
	UPlayerStateBase* currentSuperstate;
	UPlayerStateBase* currentSubstate;
	bool isRootState;
};
