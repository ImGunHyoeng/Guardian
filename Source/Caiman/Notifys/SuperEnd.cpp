// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/SuperEnd.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/SUPERARMOR_O.h"
void USuperEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			if (USUPERARMOR_O* temp = Cast<USUPERARMOR_O>(Player->getCurState()))
			{
				temp->end = true;
			}
		}
	}
}
