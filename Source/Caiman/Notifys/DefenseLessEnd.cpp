// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/DefenseLessEnd.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/DEFENSELESS_O.h"

void UDefenseLessEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			if (UDEFENSELESS_O* temp = Cast<UDEFENSELESS_O>(Player->getCurState()->GetSubState()))
			{
				Player->SetDefenseLess(true);
				//Player->SetWaitFrame(2);
			}
		}
	}
}
