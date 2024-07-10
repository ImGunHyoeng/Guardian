// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/JUMPATTACK_O.h"
#include "CCharacterPlayer.h"
#include "AnimInstance\KwangAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "FSM/PlayerStateFactory.h"
#include "Components/AttributeComponent.h"
#include "HUD/PlayerHUD.h"
#include "HUD/PlayerOverlay.h"
#include "Components/AttributeComponent.h"
void UJUMPATTACK_O::updateInput()
{
	if (end)
	{
		if (kwang)
			kwang->setJumpAttackEnd();
		SwitchState(factory->CreateD_IDLE());
		return;
	}
}

void UJUMPATTACK_O::update()
{
	ctx->Look(ctx->GetLookInputActionValue());
	updateInput();

}

void UJUMPATTACK_O::enter()
{
	ctx->GetAttribute()->SetPower(20);
	ctx->SetSheath(false);
	kwang = ctx->getAnimInstance();
	if (kwang)
	{
		kwang->setDraw();
		kwang->setJumpAttack();
	}
	end = false;
	ctx->SetUsingStamina(true);
	ctx->GetAttribute()->UseStamina(ctx->GetAttribute()->GetAttackCost());
	ctx->GetHUD()->SetStaminaBarPercent(ctx->GetAttribute()->GetStaminaPercent());
}

void UJUMPATTACK_O::exit()
{
	ctx->GetAttribute()->SetPower();
	ctx->SetUsingStamina(false);
	kwang->setJumpAttackEnd();
	end = false;
}

void UJUMPATTACK_O::Destroy()
{
}

void UJUMPATTACK_O::InitializeSubState()
{
}
