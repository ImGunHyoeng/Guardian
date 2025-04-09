// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UMatetrialParameterHelper.generated.h"

/**
 * 
 */
UCLASS()
class CAIMAN_API UUMatetrialParameterHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Material")
	static void SetIntParamIfExists(UMaterialInstanceDynamic* Material, FName ParamName, int32 IntValue);
};
