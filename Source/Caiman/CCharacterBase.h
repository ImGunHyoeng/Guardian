// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacterBase.generated.h"

UCLASS()
class CAIMAN_API ACCharacterBase : public ACharacter
{
	/*GENERATED_BODY()

public:
	ACCharacterBase();

protected:

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; 

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cameara")
		TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Cameara")
		TObjectPtr<class UCameraComponent> Camera;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> RunningAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> DashAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UInputAction> LookAction;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation/Dash", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<class UAnimMontage> DashMontage;


protected:
	void OnMove(const FInputActionValue& Value);
	void OnLook(const FInputActionValue& Value);

	bool bIsRunning = false;
	void OnRunning();
	void OffRunning();

	bool bIsDash = false;
	void OnDash();

public:
	UFUNCTION(BlueprintCallable)
		bool GetIsRunning();*/
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACCharacterBase();
	void BeginPlay();
	void Tick(float DeltaTime);
public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	//UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))//Meta: 프라이빗의 값을 가지고 있어도 에디터에서 접근되도록 하는것
	//	TMap<ECharacterControlType, class UABCharacterControlDataAsset*> CharacterControlManager;

	//virtual void SetCharacterControlData(const UABCharacterControlDataAsset* CharacterControlData);//앞에서 전방위 선언을 했기에 중복 사용안한
};
