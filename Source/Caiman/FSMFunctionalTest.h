// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "FSMFunctionalTest.generated.h"

/**
 * 
 */
UCLASS()
class CAIMAN_API AFSMFunctionalTest : public AFunctionalTest
{
	GENERATED_BODY()
	AFSMFunctionalTest();

protected:
	//UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="FSM test data")
	//TObjectPtr<class ACCharacterPlayer> Player;
	//APlayerController* controller;
	//TObjectPtr<class UEnhancedInputLocalPlayerSubsystem> Subsystem;
	//TObjectPtr<class UEnhancedPlayerInput> PlayerInput;
	//TObjectPtr<class UInputAction> InputAction;
	virtual void BeginPlay()override;
	virtual void Tick(float DeltaTime) override;
	bool bactivateFireInputAction = false;
	


};
