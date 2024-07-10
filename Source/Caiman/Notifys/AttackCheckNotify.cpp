// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/AttackCheckNotify.h"
#include "CCharacterPlayer.h"
//#include "FSM/OBJECT_STATE/OFSMCollection.h"
#include "FSM/OBJECT_STATE/ATTACK_O.h"

void UAttackCheckNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{

	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
			//ATTACK* AT = Cast<ATTACK,IIPlayerState>(Player->GetCurPlayerState());
			//if (AT)
			//{
			//	(AT)->AttackStateDoing();
			//}
			//UE_LOG(LogTemp, Warning, TEXT("playerState class: %s"), (Player->GetCurPlayerState())->_getUObject());
			//=Cast<ATTACK>(Player->GetCurPlayerState());
			UATTACK_O* AT=Cast<UATTACK_O>(Player->GetCurPlayerState());
			
			if(AT)
				AT->AttackStateDoing();
			
		}
	}
}

void UAttackCheckNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (MeshComp)
	{
		ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
		if (Player)
		{
	/*		ATTACK* AT=Cast<ATTACK>(Player->GetCurPlayerState());
			if (AT)
			{
				(AT)->AttackStateDone();
			}*/
			////Attack *AT=Cast<ATTACK>(Player->GetCurPlayerState());
			UATTACK_O* AT = Cast<UATTACK_O>(Player->GetCurPlayerState());
			if (AT)
				AT->AttackStateDone();
						
		}
	}
}
