// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifys/IsLeftMousePressing.h"
#include "CCharacterPlayer.h"
#include "FSM/OBJECT_STATE/ATTACK_O.h"
void UIsLeftMousePressing::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp)
		return;
	
	ACCharacterPlayer* Player = Cast<ACCharacterPlayer>(MeshComp->GetOwner());
	if (!Player)
		return;
		
	UATTACK_O* AT = Cast<UATTACK_O>(Player->GetCurPlayerState()->GetSubState());
	if (!AT)
		return;
	if (Player->getPlayerController()->IsInputKeyDown(EKeys::LeftMouseButton))
		AT->ChangeChargeAttack();
			
		
		
	
}
