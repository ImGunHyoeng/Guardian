// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayerController.h"

void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 마우스 게임 화면 포커싱
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
