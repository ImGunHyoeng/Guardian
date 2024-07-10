// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/S_IDLE_O.h"
#include "CCharacterPlayer.h"
#include "AnimInstance\KwangAnimInstance.h"
#include "FSM/PlayerStateFactory.h"
#include "Components/AttributeComponent.h"

void US_IDLE_O::updateInput()
{
	if (ctx->getPlayerController()->WasInputKeyJustPressed(EKeys::LeftControl))
	{
		if (ctx->HasEnoughStamina(ctx->GetAttribute()->GetRollCost()))
		{
			ctx->StopMove();
			ctx->GetCurPlayerState()->SwitchState(factory->CreateINVINCIBILITY());
			return;
		}
		
		if (!ctx->HasEnoughStamina(ctx->GetAttribute()->GetRollCost()))
		{
			ctx->StopMove();
			SwitchState(factory->CreateDEFENSELESS());
			return;
		}
	}
	if (ctx->getPlayerController()->WasInputKeyJustPressed(EKeys::SpaceBar))
	{
		SwitchState(factory->CreateJUMP());
		return;
	}
	if (ctx->getPlayerController()->WasInputKeyJustPressed(EKeys::R))
	{
		ctx->Draw();
		SwitchState(factory->CreateDRAWING());
		return;
	}
	if (ctx->GetMoveInputActionValue().GetMagnitude() > 0.1f)
	{
		SwitchState(factory->CreateS_WALK());
		return;
	}
}

void US_IDLE_O::update()
{
	ctx->Look(ctx->GetLookInputActionValue());
	updateInput();
}

void US_IDLE_O::enter()
{
	kwang = ctx->getAnimInstance();
	if (kwang)
		kwang->setSheath();
}

void US_IDLE_O::exit()
{
}

void US_IDLE_O::Destroy()
{
}

void US_IDLE_O::InitializeSubState()
{
}
