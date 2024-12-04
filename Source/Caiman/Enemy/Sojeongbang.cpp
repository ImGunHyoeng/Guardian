// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Sojeongbang.h"
#include "Components/AttributeComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/HealthBarComponent.h"
#include "CCharacterPlayer.h"


float ASojeongbang::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	isAttacked = true;
	Attributes->ReceiveDamage(DamageAmount);
	if (!player)
		player = Cast<ACCharacterPlayer>(DamageCauser->GetOwner());
	player->BossHpUpdate(Attributes->GetHealthPercent());
	//Cast<ACCharacterPlayer>(DamageCauser->GetOwner())->EnemyDie();
	//HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
	if (ones)
		return DamageAmount;
	if (!Attributes->IsAlive())
	{


			ones = true;
			PlayAnimMontage(AM_DeadReact);
			player->BossHpUpdate(0);
			Dead();
			Clear(player);

			Cast<ACCharacterPlayer>(DamageCauser->GetOwner())->EnemyDie();

			//HealthBarWidget->SetVisibility(false);
			Excute(false);
			SetLifeSpan(5.0f);
			return DamageAmount;

	}
	
	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(AM_HitReact))
		StopAnimMontage();
	PlayAnimMontage(AM_HitReact);

	return DamageAmount;
}

void ASojeongbang::HitReact(const FVector& ImpactPoint)
{
}

void ASojeongbang::DeadReact(const FVector& ImpactPoint)
{
}

void ASojeongbang::Excute(bool condition)
{
	MyParamDelegate.ExecuteIfBound(condition);
}
