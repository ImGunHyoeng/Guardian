// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/JUMP_O.h"
#include "CCharacterPlayer.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "AnimInstance/KwangAnimInstance.h"
#include "FSM/PlayerStateFactory.h"
#include "Components/AttributeComponent.h"

void UJUMP_O::updateInput()
{
	if (ctx->getPlayerController()->WasInputKeyJustPressed(EKeys::LeftMouseButton))
	{

		if (ctx->HasEnoughStamina(ctx->GetAttribute()->GetAttackCost()))
		{
			ctx->NoAnimDraw();
			//return NewObject<AJUMPATTACK_A>();
			SwitchState(factory->CreateJUMPATTACK());
		}
		return;
	}
	if (!(ctx->GetCharacterMovement()->IsFalling()))
	{
		//return NewObject<AGROUNDED_A>();
		SwitchState(factory->CreateGROUNDED());
		return;
	}
}

void UJUMP_O::update()
{
	ctx->Look(ctx->GetLookInputActionValue());
	updateInput();
}

void UJUMP_O::enter()
{
	kwang = ctx->getAnimInstance();
	if (kwang)
		kwang->setJump();
	ctx->Super::Jump();
}

void UJUMP_O::exit()
{
	if (kwang)
		kwang->setJumpEnd();
}

void UJUMP_O::Destroy()
{
}

void UJUMP_O::InitializeSubState()
{
}
