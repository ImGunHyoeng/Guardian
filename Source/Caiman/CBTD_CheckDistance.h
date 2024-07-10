// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CBTD_CheckDistance.generated.h"

/**
 * 
 */
UCLASS()
class CAIMAN_API UCBTD_CheckDistance : public UBTDecorator
{
	GENERATED_BODY()
public:
	UCBTD_CheckDistance();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
