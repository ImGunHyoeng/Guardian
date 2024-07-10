// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/ParringEnd.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/PARRING_O.h"

void UParringEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			if (UPARRING_O* temp = Cast<UPARRING_O>(Player->getCurState()->GetSubState()))
			{
				Player->SetParringEnd(true);
				//Player->SetWaitFrame(2);
			}
		}
	}
}
