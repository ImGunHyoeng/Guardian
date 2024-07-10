// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/PARRING_O.h"
#include "AnimInstance\KwangAnimInstance.h"
#include "CCharacterPlayer.h"
#include "FSM/PlayerStateFactory.h"

void UPARRING_O::updateInput()
{
}

void UPARRING_O::update()
{
	ctx->Look(ctx->GetLookInputActionValue());
	updateInput();
}

void UPARRING_O::enter()
{
	kwang = ctx->getAnimInstance();
	ctx->PlayAnimMontage(ctx->GetParringMontage(), 1.0f);
	//ctx->SetWaitFrame(30);
	ctx->SetParring(true);
	ctx->SetParringEnd(false);
}

void UPARRING_O::exit()
{
	ctx->SetParring(false);
	//ctx->SetWaitFrame(0);
}

void UPARRING_O::Destroy()
{
}

void UPARRING_O::InitializeSubState()
{
}
