// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/PlayerStateBase.h"
#include "CCharacterPlayer.h"

void UPlayerStateBase::UpdateStates()
{
	if (this == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Null"));
		return;
	}
	update();
	if (currentSubstate == NULL)
		return;
	currentSubstate->UpdateStates();
}

void UPlayerStateBase::EnterStates()
{
	if (this == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Null"));
		return;
	}
	enter();
	if (currentSubstate == NULL)
		return;
	currentSubstate->EnterStates();
}

void UPlayerStateBase::ExitStates()
{
	if (this == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Null"));
		return;
	}
	exit();
	if (currentSubstate == NULL)
		return;
	currentSubstate->ExitStates();
}

UPlayerStateBase::UPlayerStateBase()
{
}

void UPlayerStateBase::SetInitalProperty(ACCharacterPlayer* _ctx, UPlayerStateFactory* _factory)
{
	ctx = _ctx;
	factory = _factory;
}

void UPlayerStateBase::SetRoot(bool _input)
{
	isRootState = _input;
}

void UPlayerStateBase::SwitchState(UPlayerStateBase* newState)
{
	ExitStates();
	newState->EnterStates();
	UE_LOG(LogTemp, Warning, TEXT("Switch Call"));
	if (isRootState)
		ctx->setCurState(newState);
	else if (currentSuperstate != NULL)
	{
		currentSuperstate->SetSubState(newState);
	}
}

UPlayerStateBase* UPlayerStateBase::GetSubState()
{
	return currentSubstate;
}

void UPlayerStateBase::SetSuperState(UPlayerStateBase* newSuperState)
{
	currentSuperstate = newSuperState;
}

void UPlayerStateBase::SetSubState(UPlayerStateBase* newSubState)
{
	currentSubstate = newSubState;
	newSubState->SetSuperState(this);
}
