// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/RollEnd.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/S_ROLL_O.h"

void URollEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			if (US_ROLL_O* temp = Cast<US_ROLL_O>(Player->getCurState()->GetSubState()))
			{
				temp->isRoll = false;
				Player->SetWaitFrame(2);
			}
		}
	}
}
