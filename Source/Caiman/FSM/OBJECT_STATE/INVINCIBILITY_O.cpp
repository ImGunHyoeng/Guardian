// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/INVINCIBILITY_O.h"
#include "AnimInstance\KwangAnimInstance.h"
#include "CCharacterPlayer.h"
#include "FSM/PlayerStateFactory.h"
#include "Components/AttributeComponent.h"

void UINVINCIBILITY_O::updateInput()
{
	if (ctx->GetParringEnd() == true)
	{
		SwitchState(factory->CreateNORMAL());
		return;
	}
	if (ctx->GetParringSuccessEnd() == true)
	{
		SwitchState(factory->CreateNORMAL());
		return;
	}
}

void UINVINCIBILITY_O::update()
{
	updateInput();
}

void UINVINCIBILITY_O::enter()
{
	InitializeSubState();
	UE_LOG(LogTemp, Warning, TEXT("AINVINCIBILITY_A"));
}

void UINVINCIBILITY_O::InitializeSubState()
{
	if (ctx->getPlayerController()->WasInputKeyJustPressed(EKeys::LeftControl))
	{
		
		ctx->StopMove();
		SetSubState(factory->CreateS_ROLL());
		return;
	}
	if (ctx->getPlayerController()->WasInputKeyJustPressed(EKeys::Q))
	{
		SetSubState(factory->CreatePARRING());
		return;
	}
}

void UINVINCIBILITY_O::exit()
{
}

void UINVINCIBILITY_O::Destroy()
{
}
