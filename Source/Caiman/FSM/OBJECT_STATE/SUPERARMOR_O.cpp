// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/SUPERARMOR_O.h"
#include "FSM/PlayerStateFactory.h"
#include "CCharacterPlayer.h"

USUPERARMOR_O::USUPERARMOR_O()
{
}

void USUPERARMOR_O::updateInput()
{
	if (end)
	{
		SwitchState(factory->CreateNORMAL());
	}
}

void USUPERARMOR_O::update()
{
	updateInput();
}

void USUPERARMOR_O::enter()
{
	InitializeSubState();
	end = false;
}

void USUPERARMOR_O::InitializeSubState()
{//동시에 누르기
	if (ctx->getPlayerController()->IsInputKeyDown(EKeys::LeftMouseButton) && ctx->getPlayerController()->IsInputKeyDown(EKeys::C))
	{
		ctx->PlayAnimMontage(ctx->GetChargeAttackMontage(), 1.0f, FName("ChargingStart"));
		SetSubState(factory->CreateSUPERCHARGINGATTACK());
	}
}

void USUPERARMOR_O::exit()
{
	end = false;
}

void USUPERARMOR_O::Destroy()
{
}
