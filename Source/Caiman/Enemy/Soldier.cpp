// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Soldier.h"
#include "Item/CWeaponSTM.h"
#include "Components/AttributeComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/HealthBarComponent.h"

float ASoldier::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	isAttacked = true;
	Attributes->ReceiveDamage(DamageAmount);
	HealthBarWidget->SetHealthPercent(Attributes->GetHealthPercent());
	if (!Attributes->IsAlive())
	{
		PlayAnimMontage(AM_DeadReact);
		HealthBarWidget->SetVisibility(false);
		Dead();
		SetLifeSpan(5.0f);
		return DamageAmount;
	}
	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(AM_HitReact))
		StopAnimMontage();
	PlayAnimMontage(AM_HitReact);

	return DamageAmount;
}

void ASoldier::BeginPlay()
{
	Super::BeginPlay();
	//FName WeaponSocket(TEXT("Weapon"));
	//if (WeaponClass)
	//{
	//	Weapon = GetWorld()->SpawnActor<ACWeaponSTM>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
	//	Weapon->SetOwner(this);
	//}
	////무기 손에 붙이기
	//if (Weapon)
	//{
	//	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
	//}
}

void ASoldier::DeadReact(const FVector& ImpactPoint)
{
}

