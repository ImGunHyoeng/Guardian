// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimNotifyState_Trace.h"
#include "CCharacterPlayer.h"
#include "CTraceComponent.h"
#include "Item/CMyWeapon.h"

void UCAnimNotifyState_Trace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	
	Super::NotifyBegin(MeshComp, Animation,TotalDuration,EventReference);

	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			Player->GetWeapon()->getTrace()->TsetActive();	
		}
	}
}



void UCAnimNotifyState_Trace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			Player->GetWeapon()->getTrace()->TsetActive(false);
		}
	}

}
