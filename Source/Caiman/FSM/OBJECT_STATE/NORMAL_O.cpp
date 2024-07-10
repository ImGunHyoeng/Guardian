// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/NORMAL_O.h"
#include "FSM/PlayerStateFactory.h"
#include "CCharacterPlayer.h"

void UNORMAL_O::updateInput()
{
}

void UNORMAL_O::update()
{
	updateInput();
}

void UNORMAL_O::enter()
{
	UE_LOG(LogTemp, Warning, TEXT("Normal"));
	InitializeSubState();
}

void UNORMAL_O::InitializeSubState()
{
	if (ctx->GetParringEnd() == true)
	{
		SetSubState(factory->CreateDEFENSELESS());
		return;
	}
	if (ctx->GetParringSuccessEnd() == true)
	{
		SetSubState(factory->CreateD_IDLE());
		ctx->SetParringSuccessEnd(false);
		return;
	}
	if (ctx->GetSheath())
	{
		SetSubState((factory->CreateS_Rest()));
		//SetSubState((factory->CreateS_IDLE()));
		return;
	}
	if (ctx->GetSheath() == false)
	{
		SetSubState((factory->CreateD_Rest()));
		//SetSubState((factory->CreateD_IDLE()));
		return;
	}
}

void UNORMAL_O::exit()
{
}

void UNORMAL_O::Destroy()
{
}
