// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/S_REST_O.h"
#include "FSM/PlayerStateFactory.h"
#include "CCharacterPlayer.h"
US_REST_O::US_REST_O()
{
}

void US_REST_O::updateInput()
{
	if (IsEnd)
	{
		ctx->StopAnimMontage();
		SwitchState(factory->CreateS_IDLE());
	}
}

void US_REST_O::update()
{
	updateInput();
}

void US_REST_O::enter()
{
	ctx->PlayAnimMontage(ctx->GetS_RestMontage(), 1.0f);
	IsEnd = false;
}

void US_REST_O::InitializeSubState()
{
}

void US_REST_O::exit()
{
	IsEnd = false;
}

void US_REST_O::Destroy()
{
}
