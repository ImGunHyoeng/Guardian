// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/SUPERCHARGINGATTACK_O.h"
#include "CCharacterPlayer.h"
#include "Components/AttributeComponent.h"
void USUPERCHARGINGATTACK_O::updateInput()
{
	Super::updateInput();
}

void USUPERCHARGINGATTACK_O::update()
{
	Super::update();//업데이트에서 이미 진행함. this의 업데이트 input으로 들어가기에 아니다.
}

void USUPERCHARGINGATTACK_O::enter()
{
	Super::enter();
	ctx->GetAttribute()->SetPower(5);
	ctx->SetNaiagra();
}

void USUPERCHARGINGATTACK_O::exit()
{
	Super::exit();
	ctx->GetAttribute()->SetPower();
	ctx->DeActiveNaiagra();
}

void USUPERCHARGINGATTACK_O::Destroy()
{
}

void USUPERCHARGINGATTACK_O::InitializeSubState()
{
}
