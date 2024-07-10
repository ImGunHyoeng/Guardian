// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/D_WALK_O.h"
#include "CCharacterPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FSM/PlayerStateFactory.h"
#include "Components/AttributeComponent.h"

void UD_WALK_O::updateInput()
{
	if (ctx->getPlayerController()->IsInputKeyDown(EKeys::LeftMouseButton) && ctx->getPlayerController()->IsInputKeyDown(EKeys::C))
	{
		currentSuperstate->SwitchState(factory->CreateSUPERARMOR());
		return;
	}
	if (ctx->getPlayerController()->WasInputKeyJustPressed(EKeys::Q))
	{
		ctx->GetCurPlayerState()->SwitchState(factory->CreateINVINCIBILITY());
		return;
	}
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
	if (ctx->GetMoveInputActionValue().GetMagnitude() < 0.1f)
	{
		SwitchState(factory->CreateD_IDLE());
		return;
	}
	if (ctx->getPlayerController()->WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{

		if (ctx->HasEnoughStamina(ctx->GetAttribute()->GetAttackCost()))
		{

			//ctx->SetWaitFrame(70);
			SwitchState(factory->CreateATTACK());
			return;
		}
		if (!ctx->HasEnoughStamina(ctx->GetAttribute()->GetAttackCost()))
		{
			ctx->StopMove();
			SwitchState(factory->CreateDEFENSELESS());
			return;
		}
		
	}
	if (ctx->getPlayerController()->WasInputKeyJustPressed(EKeys::R))
	{
		ctx->Sheath();
		SwitchState(factory->CreateSHEATHING());
		return;
	}
}

void UD_WALK_O::update()
{
	ctx->Move(ctx->GetMoveInputActionValue());
	ctx->Look(ctx->GetLookInputActionValue());
	updateInput();
}

void UD_WALK_O::enter()
{
	ctx->GetCharacterMovement()->MaxWalkSpeed = 1000 / 3.0f;
}

void UD_WALK_O::exit()
{
}

void UD_WALK_O::Destroy()
{
}

void UD_WALK_O::InitializeSubState()
{
}
