// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Hit\HitInterface.h"
#include "GuardianEnemyBase.generated.h"

class ACWeaponSTM;
class UAttributeComponent;
class UHealthBarComponent;
UCLASS()
class CAIMAN_API AGuardianEnemyBase : public ACharacter, public IHitInterface
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
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Offense) override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnyWhere, Category = "Collision")
	class UCapsuleComponent* Body;

	UPROPERTY(VisibleAnyWhere, Category = "Collision")
	USkeletalMeshComponent* Bone;

	class ACCharacterPlayer* player;

	UPROPERTY(EditAnywhere, Category = VisualEffect)
	UParticleSystem* HittedParticle;

	FVector  spawnpoint;
	FVector  targetLocation;

	UPROPERTY(BlueprintReadOnly,EditAnyWhere, Category = "Montage")
	UAnimMontage* AM_HitReact;
	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category = "Montage")
	UAnimMontage* AM_DeadReact;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Montage")
	UAnimMontage* AM_Attack;

	UPROPERTY(EditAnywhere, Category = VisualEffect)
	UParticleSystem* ParringParticle;
	UPROPERTY(EditAnywhere, Category = HittedSound)
	class USoundBase* ThunderSound;

	UPROPERTY(BlueprintReadWrite,VisibleAnyWhere)
	bool isAttacked;
	UPROPERTY(BlueprintReadWrite,VisibleAnyWhere)
	bool isAttack;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TSubclassOf<ACWeaponSTM> WeaponClass;

	ACWeaponSTM* Weapon;

	UPROPERTY(BlueprintReadWrite, VisibleAnyWhere)
	bool AttackRange;

	virtual void HitReact(const FVector& ImpactPoint);
	virtual void DeadReact(const FVector& ImpactPoint);

	UPROPERTY(VisibleAnyWhere, Category = "Collision")
	class USphereComponent* AttackStartRange;

	UPROPERTY(VisibleAnyWhere, Category = "Collision")
	class USphereComponent* AttackEndRange;

	UPROPERTY(VisibleAnyWhere, Category = "Collision")
	class USphereComponent* DetectRange;

	UFUNCTION(BlueprintCallable)
	void SetWidgetVisible(bool input);
	///속성창
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UAttributeComponent* Attributes;
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;
	void Dead();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool ones = false;
};
