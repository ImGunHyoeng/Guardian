// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GuardianEnemyBase.generated.h"


UCLASS()
class CAIMAN_API AGuardianEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGuardianEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnyWhere, Category = "Collision")
	class UCapsuleComponent* Body;

	class ACCharacterPlayer* player;

	UPROPERTY(EditAnywhere, Category = VisualEffect)
	UParticleSystem* HittedParticle;

	FVector  spawnpoint;
	FVector  targetLocation;

	UPROPERTY(EditAnyWhere, Category = "Montage")
	UAnimMontage* AM_HitReact;
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* AM_DeadReact;


	void HitReact(const FVector& ImpactPoint);
	void DeadReact(const FVector& ImpactPoint);

	class UEnemyInstance* enemyaniminstance;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
