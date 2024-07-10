// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerOverlay.generated.h"

/**
 * 
 */
class UProgressBar;
UCLASS()
class CAIMAN_API UPlayerOverlay : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetHealthBarPercent(float Percent);
	void SetStaminaBarPercent(float Percent);
	UFUNCTION(BlueprintImplementableEvent)
	void CheckClearCondition();
private:
	UPROPERTY(BlueprintReadOnly,meta=(BindWidget, AllowPrivateAccess = true))
	UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadOnly,meta = (BindWidget, AllowPrivateAccess = true))
	UProgressBar* StaminaBar;
	
};
