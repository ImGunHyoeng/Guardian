// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/S_WALK_O.h"
#include "CCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FSM/PlayerStateFactory.h"
#include "Components/AttributeComponent.h"

void US_WALK_O::updateInput()
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
	if (ctx->getPlayerController()->IsInputKeyDown(EKeys::LeftShift))
	{
		if (ctx->HasEnoughStamina(ctx->GetAttribute()->GetRunCost()))
		{
			SwitchState(factory->CreateS_RUN());
		}
		return;
	}
	if (ctx->GetMoveInputActionValue().GetMagnitude() < 0.1f)
	{
		SwitchState(factory->CreateS_IDLE());
		return;
	}
	if (ctx->getPlayerController()->WasInputKeyJustPressed(EKeys::R))
	{
		ctx->Draw();
		SwitchState(factory->CreateDRAWING());
		return;
	}
	if (ctx->getPlayerController()->WasInputKeyJustPressed(EKeys::SpaceBar))
	{
		SwitchState(factory->CreateJUMP());
		return;
	}
}

void US_WALK_O::update()
{
	ctx->Look(ctx->GetLookInputActionValue());
	ctx->Move(ctx->GetMoveInputActionValue());
	updateInput();
}

void US_WALK_O::enter()
{
	ctx->GetCharacterMovement()->MaxWalkSpeed = 1000 / 2.0f;
}

void US_WALK_O::exit()
{
}

void US_WALK_O::InitializeSubState()
{
}

void US_WALK_O::Destroy()
{
}
