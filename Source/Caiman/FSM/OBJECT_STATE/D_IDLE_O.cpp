// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/D_IDLE_O.h"
#include "FSM/PlayerStateFactory.h"
#include "CCharacterPlayer.h"
#include "AnimInstance\KwangAnimInstance.h"
#include "Components/AttributeComponent.h"

void UD_IDLE_O::updateInput()
{
	if (ctx->getPlayerController()->IsInputKeyDown(EKeys::LeftMouseButton) && ctx->getPlayerController()->IsInputKeyDown(EKeys::C))
	{
		currentSuperstate->SwitchState(factory->CreateSUPERARMOR());
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
	if (ctx->getPlayerController()->WasInputKeyJustPressed(EKeys::Q))
	{
		ctx->GetCurPlayerState()->SwitchState(factory->CreateINVINCIBILITY());
		return;
	}
	if (ctx->getPlayerController()->WasInputKeyJustPressed(EKeys::R))
	{
		ctx->Sheath();
		SwitchState(factory->CreateSHEATHING());
		return;
	}
	if (ctx->GetMoveInputActionValue().GetMagnitude() > 0.1f)
	{
		SwitchState(factory->CreateD_WALK());
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
}

void UD_IDLE_O::update()
{
	ctx->Look(ctx->GetLookInputActionValue());
	updateInput();
}

void UD_IDLE_O::enter()
{
	ctx->SetSheath(false);
	kwang = ctx->getAnimInstance();
	if (kwang)
		kwang->setDraw();
}

void UD_IDLE_O::exit()
{
}

void UD_IDLE_O::Destroy()
{
}

void UD_IDLE_O::InitializeSubState()
{
}
