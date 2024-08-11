// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeaponSTM.generated.h"

class UCTraceComponent;
UCLASS()
class CAIMAN_API ACWeaponSTM : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACWeaponSTM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UCTraceComponent* getTrace()
	{
		return trace;
	}

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Values)
	float Power;
	UFUNCTION(BlueprintPure)
	float getPower() const { return Power; }

	UFUNCTION(BlueprintCallable)
	void setPower(float input) { Power = input; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCTraceComponent* trace;

	UFUNCTION(BlueprintCallable)
	UParticleSystem* GetHitParticle() { return HitParticle; }
	UFUNCTION(BlueprintCallable)
	UParticleSystem* GetJumpAttackParticle() { return JumpAttackParticle; }
	UPROPERTY(EditAnywhere, Category = VisualEffect)
	UParticleSystem* HitParticle;
	UPROPERTY(EditAnywhere, Category = VisualEffect)
	UParticleSystem* JumpAttackParticle;

};
