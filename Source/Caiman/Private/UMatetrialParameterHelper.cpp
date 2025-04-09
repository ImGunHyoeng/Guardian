// Fill out your copyright notice in the Description page of Project Settings.


#include "UMatetrialParameterHelper.h"

void UUMatetrialParameterHelper::SetIntParamIfExists(UMaterialInstanceDynamic* Material, FName ParamName, int32 IntValue)
{
	TArray<FMaterialParameterInfo> ParamInfos;
	TArray<FGuid> ParamIds;

	Material->GetAllScalarParameterInfo(ParamInfos, ParamIds);

	for (const FMaterialParameterInfo& Info : ParamInfos)
	{
		if (Info.Name == ParamName)
		{
			Material->SetScalarParameterValue(ParamName, (float)IntValue);
			UE_LOG(LogTemp, Log, TEXT("Set int-like param '%s' to %d"), *ParamName.ToString(), IntValue);
			return;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Param '%s' not found."), *ParamName.ToString());
}
