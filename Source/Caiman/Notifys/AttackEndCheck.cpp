// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/AttackEndCheck.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/ATTACK_O.h"

void UAttackEndCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{

			if (UATTACK_O* currentState = Cast<UATTACK_O>(Player->GetCurPlayerState()->GetSubState()))
			{
				currentState->AttackStateEnd();
			}
		}
	}
}
