// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAIMAN_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void ReceiveDamage(float Damage);
	UFUNCTION(BlueprintCallable)
	void UseStamina(float StaminaCost);

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent();
	UFUNCTION(BlueprintCallable)
	float GetStaminaPercent();
	void RegenStamina(float DeltaTime);
	bool IsAlive();

	FORCEINLINE float GetRollCost()const { return RollCost; }
	FORCEINLINE float GetRunCost()const { return RunCost; }
	FORCEINLINE float GetAttackCost()const { return AttackCost; }
	FORCEINLINE float GetChargeCost()const { return ChargeCost; }
	FORCEINLINE float GetMaxStamina()const { return MaxStamina; }
	
	FORCEINLINE float GetPower()const { return Power; }
	FORCEINLINE void SetPower(float input=10) { Power = input; }
private:
	UPROPERTY(EditAnywhere,Category="Attributes")
	float Health;

	UPROPERTY(EditAnywhere,Category="Attributes")
	float MaxHealth;
	
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float Stamina;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float MaxStamina;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float RollCost=16;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float AttackCost = 8;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float RunCost = 5;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float ChargeCost = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Attributes")
	float StaminaRegenRate = 6;
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float Power = 10;
};
