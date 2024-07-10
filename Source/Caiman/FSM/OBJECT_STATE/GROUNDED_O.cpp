// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/GROUNDED_O.h"
#include "CCharacterPlayer.h"
#include "AnimInstance\KwangAnimInstance.h"
#include "FSM/PlayerStateFactory.h"


void UGROUNDED_O::updateInput()
{
	if (end)
	{
		SwitchState(factory->CreateS_IDLE());
		return;
	}
	if (ctx->GetMoveInputActionValue().GetMagnitude() > 0.1f && canChange)
	{
		SwitchState(factory->CreateS_IDLE());
		return;
	}
}

void UGROUNDED_O::update()
{
	updateInput();
}

void UGROUNDED_O::enter()
{
	kwang = ctx->getAnimInstance();
	end = false;
	canChange = false;
}

void UGROUNDED_O::exit()
{
	end = false;
	canChange = false;
}

void UGROUNDED_O::Destroy()
{
	
}

void UGROUNDED_O::InitializeSubState()
{
}
