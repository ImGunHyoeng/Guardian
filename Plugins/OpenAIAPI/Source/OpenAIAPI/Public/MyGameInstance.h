// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class OPENAIAPI_API UMyGameInstance : public UGameInstance
{
public:
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BluePrintReadWrite)
	bool midSave=false;
	virtual void Init() override;
	
};
