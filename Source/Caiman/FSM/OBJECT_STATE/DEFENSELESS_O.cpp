// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/DEFENSELESS_O.h"
#include "CCharacterPlayer.h"
#include "AnimInstance\KwangAnimInstance.h"
#include "FSM/PlayerStateFactory.h"

void UDEFENSELESS_O::updateInput()
{
	if (ctx->GetDefenseLess() == true)
	{
		ctx->GetCurPlayerState()->SwitchState(factory->CreateNORMAL());
		return;
	}
}

void UDEFENSELESS_O::update()
{
	ctx->Look(ctx->GetLookInputActionValue());
	updateInput();
}

void UDEFENSELESS_O::enter()
{
	ctx->SetParring(false);
	kwang = ctx->getAnimInstance();
	ctx->PlayAnimMontage(ctx->GetDefenseLessMontage(), 1.0f);
	//if (kwang)
	//	kwang->setDraw();
	//ctx->SetWaitFrame(20);
	ctx->SetDefenseLess(false);
}

void UDEFENSELESS_O::exit()
{
	ctx->SetParringEnd(false);
}

void UDEFENSELESS_O::Destroy()
{
}

void UDEFENSELESS_O::InitializeSubState()
{
}
