// Fill out your copyright notice in the Description page of Project Settings.


#include "FSM/OBJECT_STATE/KNOCKBACK_O.h"
#include "CCharacterPlayer.h"
#include "FSM/PlayerStateFactory.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AttributeComponent.h"
UKNOCKBACK_O::UKNOCKBACK_O()
{
}

void UKNOCKBACK_O::updateInput()
{
	if (can)
	{
		if (ctx->getPlayerController()->WasInputKeyJustPressed(EKeys::LeftControl))
		{
			if (ctx->HasEnoughStamina(ctx->GetAttribute()->GetRollCost()))
			{
				ctx->StopAnimMontage();
				currentSuperstate->SwitchState(factory->CreateINVINCIBILITY());
				return;
			}
		}
		
	}
	if (end)
	{
		ctx->StopAnimMontage();
		currentSuperstate->SwitchState(factory->CreateNORMAL());
		return;
	}
}

void UKNOCKBACK_O::update()
{
	ctx->Look(ctx->GetLookInputActionValue());
	updateInput();
}

void UKNOCKBACK_O::enter()
{
	end = false;
	can = false;
}

void UKNOCKBACK_O::InitializeSubState()
{
}

void UKNOCKBACK_O::exit()
{
	end = false;
	can = false;
}

void UKNOCKBACK_O::Destroy()
{
}

void UKNOCKBACK_O::SetPoint(const FVector& ImpactPoint)
{
	ParticlePoint = ImpactPoint;
}

void UKNOCKBACK_O::Start()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ctx->GetHittedParticle(), ParticlePoint);
	FVector forward = ctx->GetActorForwardVector();
	FVector hitno_z = FVector(ParticlePoint.X, ParticlePoint.Y, ctx->GetActorLocation().Z);
	FVector toHit = (hitno_z - ctx->GetActorLocation()).GetSafeNormal();
	float cos = FVector::DotProduct(forward, toHit);
	float seta = acos(cos);
	float degree = FMath::RadiansToDegrees(seta);
	FVector Cross = FVector::CrossProduct(forward, toHit);
	if (Cross.Z < 0)
		degree *= -1;
	UKismetSystemLibrary::DrawDebugArrow(this, ctx->GetActorLocation(), ctx->GetActorLocation() + forward * 50, 5, FColor::Red, 15);
	UKismetSystemLibrary::DrawDebugArrow(this, ctx->GetActorLocation(), ctx->GetActorLocation() + toHit * 50, 5, FColor::Green, 15);
	UKismetSystemLibrary::DrawDebugArrow(this, ctx->GetActorLocation(), ctx->GetActorLocation() + Cross * 50, 5, FColor::Blue, 15);
	FName Section("Back");

	if (degree >= -45.f && degree < 45.f)
	{
		Section = FName("Foward");
	}
	else if (degree >= -135.f && degree < -45.f)
	{
		Section = FName("Left");
	}
	else if (degree >= 45.f && degree < 135.f)
	{
		Section = FName("Right");
	}

	ctx->PlayAnimMontage(ctx->GetHittedMontage(), 1, Section);
}
