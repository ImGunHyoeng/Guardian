// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/DRAWING_O.h"
#include "CCharacterPlayer.h"
#include "FSM/PlayerStateFactory.h"


void UDRAWING_O::updateInput()
{
	if (end)
	{
		SwitchState(factory->CreateD_IDLE());
		return;
	}
	if (ctx->GetMoveInputActionValue().GetMagnitude() > 0.1f && canChange)
	{
		ctx->StopAnimMontage(ctx->GetDrawMontage());
		SwitchState(factory->CreateD_IDLE());
		return;
	}
}

void UDRAWING_O::update()
{
	ctx->Look(ctx->GetLookInputActionValue());
	updateInput();
}

void UDRAWING_O::enter()
{
	canChange = false;
	end = false;
}

void UDRAWING_O::exit()
{
	canChange = false;
	end = false;
}

void UDRAWING_O::Destroy()
{
}

void UDRAWING_O::InitializeSubState()
{
}
