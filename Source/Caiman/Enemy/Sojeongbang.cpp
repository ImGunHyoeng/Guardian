// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Sojeongbang.h"
#include "Components/AttributeComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/HealthBarComponent.h"


float ASojeongbang::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	isAttacked = true;
	Attributes->ReceiveDamage(DamageAmount);
	HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
	if (!Attributes->IsAlive())
	{
		PlayAnimMontage(AM_DeadReact);
		HealthBarWidget->SetVisibility(false);
		SetLifeSpan(5.0f);
		return 0;
	}
	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(AM_HitReact))
		StopAnimMontage();
	PlayAnimMontage(AM_HitReact);

	return 0.0f;
}

void ASojeongbang::HitReact(const FVector& ImpactPoint)
{
}

void ASojeongbang::DeadReact(const FVector& ImpactPoint)
{
}
