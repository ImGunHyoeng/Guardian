// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayerOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"

void UPlayerOverlay::SetHealthBarPercent(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}
}

void UPlayerOverlay::SetStaminaBarPercent(float Percent)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(Percent);
	}
}

void UPlayerOverlay::ShowBossHp()
{
	if (BossHp)
	BossHp->SetVisibility(ESlateVisibility::Visible);
}

void UPlayerOverlay::HideBossHp()
{
	if (BossHp)
	BossHp->SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerOverlay::SetVisiblityBossHp(bool condition)
{
	if (BossHp)
	{
		if(condition)
			BossHp->SetVisibility(ESlateVisibility::Visible);
		else
			BossHp->SetVisibility(ESlateVisibility::Hidden);
	}
}
