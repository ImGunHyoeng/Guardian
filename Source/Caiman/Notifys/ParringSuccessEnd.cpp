// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/ParringSuccessEnd.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/PARRINGSUCCESS_O.h"
void UParringSuccessEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			if (UPARRINGSUCCESS_O* temp = Cast<UPARRINGSUCCESS_O>(Player->getCurState()->GetSubState()))
			{
				temp->end = true;
			}
		}
	}
}
