// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/CHARGINGATTACK_O.h"
#include "FSM/PlayerStateFactory.h"
#include "CCharacterPlayer.h"
#include "Components/AttributeComponent.h"
#include "HUD/PlayerHUD.h"
#include "HUD/PlayerOverlay.h"
void UCHARGINGATTACK_O::updateInput()
{
	if (!ctx->HasEnoughStamina(ctx->GetAttribute()->GetChargeCost()))
	{
		ctx->StopMove();
		ctx->StopAnimMontage();
		SwitchState(factory->CreateDEFENSELESS());
		return;
	}
	switch (curstate)
	{
	case EChargeAttackState::STAY:
	{
		if (ctx->getPlayerController()->WasInputKeyJustReleased(EKeys::LeftMouseButton))
		{
			curstate = EChargeAttackState::START;
			resultWaitTime = DoingTime + standardDoing;
			instance->Montage_JumpToSection("ChargeAttackStart");
			WaitTime = resultWaitTime;
		}
	}
	break;
	case EChargeAttackState::START:
	{

	}
	break;
	case EChargeAttackState::DOING:
	{
		if (WaitTime < 0)
		{
			curstate = EChargeAttackState::DONE;
			instance->Montage_JumpToSection("ChargeAttackEnd");
		}
	}
	break;
	case EChargeAttackState::DONE:
	{
		if (changeState)
		{
			SwitchState(factory->CreateD_IDLE());
		}
	}
	break;
	default:
		break;
	}
}

void UCHARGINGATTACK_O::update()
{
	ctx->Look(ctx->GetLookInputActionValue());
	//if(ctx->getPlayerController()->(EKeys::LeftMouseButton))이건 노티파이
	switch (curstate)
	{
	case EChargeAttackState::STAY:
	{
		ctx->GetAttribute()->UseStamina(ctx->GetAttribute()->GetChargeCost());
		ctx->GetHUD()->SetStaminaBarPercent(ctx->GetAttribute()->GetStaminaPercent());
		DoingTime += FApp::GetDeltaTime() * 2;
		DoingTime = FMath::Clamp(DoingTime, 0, ExtraTimeLimit);

	}
	break;
	case EChargeAttackState::START:
	{

	}
	break;
	case EChargeAttackState::DOING:
	{
		ctx->Move(ctx->GetMoveInputActionValue());
		WaitTime -= FApp::GetDeltaTime() * 4;
	}
	break;
	case EChargeAttackState::DONE:
	{

	}
	break;
	default:
		break;
	}
	updateInput();
}

void UCHARGINGATTACK_O::enter()
{
	//player.SetNaiagra();
	ctx->GetAttribute()->SetPower(6);
	instance = ctx->GetMesh()->GetAnimInstance();
	
	ctx->SetUsingStamina(true);
	curstate = EChargeAttackState::STAY;
	ctx->PlayAnimMontage(ctx->GetChargeAttackMontage(), 1.0f, "ChargingStay");
	DoingTime = 0;
	changeState = false;
	WaitTime = 0;
}

void UCHARGINGATTACK_O::exit()
{
	ctx->GetAttribute()->SetPower();
	curstate = EChargeAttackState::STAY;
	DoingTime = 0;
	WaitTime = 0;
	ctx->SetUsingStamina(false);
	//player.DeActiveNaiagra();
}

void UCHARGINGATTACK_O::Destroy()
{
}

void UCHARGINGATTACK_O::InitializeSubState()
{
}

void UCHARGINGATTACK_O::ChangeDoing(ACCharacterPlayer* player)
{
	player->PlayAnimMontage(player->GetChargeAttackMontage(), 1.0f, "ChargeAttackLoop");
	//instance->Montage_JumpToSection("ChargeAttackLoop");
	curstate = EChargeAttackState::DOING;
}
