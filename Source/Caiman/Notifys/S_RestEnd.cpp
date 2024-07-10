// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/S_RestEnd.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/S_REST_O.h"

void US_RestEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			if (US_REST_O* temp = Cast<US_REST_O>(Player->getCurState()->GetSubState()))
			{
				temp->IsEnd = true;
				//Player->SetWaitFrame(2);
			}
		}
	}
}
