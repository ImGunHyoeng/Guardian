// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthBarComponent.h"
#include "HUD/HealthBar.h"
#include "Components/ProgressBar.h"
void UHealthBarComponent::SetHealthPercent(float Percent)
{
	if (HealthBarWidget ==nullptr)
	{
		HealthBarWidget = Cast<UHealthBar>(GetUserWidgetObject());//현재 컴포넌트에 붙어있는 헬스바를 가져옴
	}
	
	if (HealthBarWidget&&HealthBarWidget->HealthBar)
	{
		//내가 설정한 진행바의 퍼센트를 나타냄
		HealthBarWidget->HealthBar->SetPercent(Percent);
	}

}
