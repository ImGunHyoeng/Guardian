// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/DrawAnimState.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/DRAWING_O.h"

void UDrawAnimState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			UDRAWING_O* DRAW = Cast<UDRAWING_O>(Player->GetCurPlayerState()->GetSubState());

			if (DRAW)
				DRAW->canChange = true;

		}
	}
}

void UDrawAnimState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			UDRAWING_O* DRAW = Cast<UDRAWING_O>(Player->GetCurPlayerState()->GetSubState());
			if (DRAW)
				DRAW->end = true;
		}
	}
}
