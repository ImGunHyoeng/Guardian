// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/HitedState.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/KNOCKBACK_O.h"

void UHitedState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			if (UKNOCKBACK_O* temp = Cast<UKNOCKBACK_O>(Player->getCurState()->GetSubState()))
			{
				temp->can = true;
			}
		}
	}
}

void UHitedState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			if (UKNOCKBACK_O* temp = Cast<UKNOCKBACK_O>(Player->getCurState()->GetSubState()))
			{
				temp->end = true;
			}
		}
	}
}
