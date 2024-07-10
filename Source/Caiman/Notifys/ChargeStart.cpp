// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/ChargeStart.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/CHARGINGATTACK_O.h"
void UChargeStart::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			if (UCHARGINGATTACK_O* temp = Cast<UCHARGINGATTACK_O>(Player->getCurState()->GetSubState()))
			{
				temp->ChangeDoing(Player);
			}
		}
	}
}
