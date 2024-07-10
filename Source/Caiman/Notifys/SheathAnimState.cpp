// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/SheathAnimState.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/SHEATHING_O.h"

void USheathAnimState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			USHEATHING_O* Sheath = Cast<USHEATHING_O>(Player->GetCurPlayerState()->GetSubState());

			if (Sheath)
				Sheath->canChange = true;

		}
	}
}

void USheathAnimState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			USHEATHING_O* Sheath = Cast<USHEATHING_O>(Player->GetCurPlayerState()->GetSubState());
			if (Sheath)
				Sheath->end = true;

		}
	}
}
