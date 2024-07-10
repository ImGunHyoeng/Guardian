// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/SHEATHING_O.h"
#include "CCharacterPlayer.h"
#include "FSM/PlayerStateFactory.h"



void USHEATHING_O::updateInput()
{
	if (end)
	{
		SwitchState(factory->CreateS_IDLE());
	}
	if (ctx->GetMoveInputActionValue().GetMagnitude() > 0.1f && canChange)
	{
		ctx->StopAnimMontage(ctx->GetSheathMontage());
		SwitchState(factory->CreateS_IDLE());
	}
}

void USHEATHING_O::update()
{
	ctx->Look(ctx->GetLookInputActionValue());
	updateInput();
}

void USHEATHING_O::enter()
{
	ctx->SetSheath(true);
	canChange = false;
	end = false;
}

void USHEATHING_O::exit()
{
	canChange = false;
	end = false;
}

void USHEATHING_O::InitializeSubState()
{
}

void USHEATHING_O::Destroy()
{

}
