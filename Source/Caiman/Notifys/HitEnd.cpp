// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/HitEnd.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/KNOCKBACK_O.h"
void UHitEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			if (UKNOCKBACK_O* temp = Cast<UKNOCKBACK_O>(Player->getCurState()->GetSubState()))
			{
				temp->end = true;
			}
		}
	}
}
