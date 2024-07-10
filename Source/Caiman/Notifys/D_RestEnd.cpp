// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/D_RestEnd.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/D_REST_O.h"

void UD_RestEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			if (UD_REST_O* temp = Cast<UD_REST_O>(Player->getCurState()->GetSubState()))
			{
				temp->IsEnd= true;
			}
		}
	}
}
