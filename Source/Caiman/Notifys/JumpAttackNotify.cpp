// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/JumpAttackNotify.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/JUMPATTACK_O.h"

void UJumpAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			if (UJUMPATTACK_O* temp = Cast<UJUMPATTACK_O>(Player->getCurState()->GetSubState()))
			{
				temp->end = true;
			}
		}
	}
}
