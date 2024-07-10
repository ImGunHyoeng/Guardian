// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/HIT_O.h"
#include "FSM/PlayerStateFactory.h"

void UHIT_O::updateInput()
{
}

void UHIT_O::update()
{
}

void UHIT_O::enter()
{
	InitializeSubState();
}

void UHIT_O::InitializeSubState()
{
	SetSubState(factory->CreateKNOCKBACK());
}

void UHIT_O::exit()
{
}

void UHIT_O::Destroy()
{
}
