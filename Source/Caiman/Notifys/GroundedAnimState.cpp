// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/GroundedAnimState.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/GROUNDED_O.h"

void UGroundedAnimState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			UGROUNDED_O* GROUNDED = Cast<UGROUNDED_O>(Player->GetCurPlayerState()->GetSubState());

			if (GROUNDED)
				GROUNDED->canChange = true;

		}
	}
}

void UGroundedAnimState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			UGROUNDED_O* GROUNDED = Cast<UGROUNDED_O>(Player->GetCurPlayerState()->GetSubState());

			if (GROUNDED)
				GROUNDED->end = true;
		}
	}
}
