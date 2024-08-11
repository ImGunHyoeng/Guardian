// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Sojeongbang.h"

float ASojeongbang::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	isAttacked = true;
	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(AM_HitReact))
		StopAnimMontage();
	PlayAnimMontage(AM_HitReact);
	return 0.0f;
}
