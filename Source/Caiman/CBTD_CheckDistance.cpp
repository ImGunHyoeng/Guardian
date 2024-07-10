// Fill out your copyright notice in the Description page of Project Settings.


#include "CBTD_CheckDistance.h"
#include "CCharacterPlayer.h"

UCBTD_CheckDistance::UCBTD_CheckDistance()
{
	NodeName = TEXT("CheckAttackDistance");
}
bool UCBTD_CheckDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	/*APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return false;

	ACCharacterPlayer* Target = Cast<ACCharacterPlayer>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AABAIController::Key_Target));
	if (nullptr == Target) return false;

	bool bResult = (Target->GetDistanceTo(ControllingPawn) <= 250.0f);*/
	return true;
}