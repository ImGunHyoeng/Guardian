// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/D_REST_O.h"
#include "FSM/PlayerStateFactory.h"
#include "CCharacterPlayer.h"

void UD_REST_O::updateInput()
{
	if (IsEnd)
	{
		ctx->StopAnimMontage();
		SwitchState(factory->CreateD_IDLE());
	}
}

void UD_REST_O::update()
{
	updateInput();
}

void UD_REST_O::enter()
{
	ctx->PlayAnimMontage(ctx->GetD_RestMontage(), 1.0f);
	IsEnd = false;
}

void UD_REST_O::InitializeSubState()
{
}

void UD_REST_O::exit()
{
	IsEnd = false;
}

void UD_REST_O::Destroy()
{
}
