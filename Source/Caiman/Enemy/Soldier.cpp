// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Soldier.h"
#include "Item/CWeaponSTM.h"

float ASoldier::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	isAttacked = true;
	/*if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(AM_HitReact))
		StopAnimMontage();*/
	PlayAnimMontage(AM_HitReact);
	return 0.0f;
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

