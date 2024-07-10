// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Hit\HitInterface.h"
#include "AnimalBase.generated.h"

UENUM()
enum class EAnimalState :uint8
{
	DEAD,
	HITTED,
	STROLL,
	FLEE
	
};
class UAttributeComponent;
class UHealthBarComponent;
UCLASS()
class CAIMAN_API AAnimalBase : public APawn, public IHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAnimalBase();

protected:
	// Called when the game starts or when spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	EAnimalState Curstate;
	virtual void BeginPlay() override;
	
	//UFUNCTION()
	//virtual void OutAttackRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//UFUNCTION()
	//virtual void PlayerInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//
	////FComponentBeginOverlapSignature, UPrimitiveComponent, OnComponentBeginOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex, bool, bFromSweep, const FHitResult&, SweepResult
	//UFUNCTION()
	//virtual void InAttackRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	////FComponentEndOverlapSignature, UPrimitiveComponent, OnComponentEndOverlap, UPrimitiveComponent*, OverlappedComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, int32, OtherBodyIndex

	//UFUNCTION()
	//virtual void PlayerOutRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
	virtual void FLEEInRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void FLEEOutRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Tick(float DeltaTime) override;
	//FQuat SmoothRotation( FQuat& StartRotation,  FQuat& EndRotation, float DeltaTime, float RotationSpeed);
	class UEnemyInstance* enemyaniminstance;

	virtual void Update();
	virtual void UpdateInput();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	float GetDegree(FVector dir);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class USkeletalMeshComponent* Bone;

	UPROPERTY(VisibleAnyWhere, Category = "Collision")
	class UCapsuleComponent* Body;

	UPROPERTY(VisibleAnyWhere, Category = "Collision")
	class USphereComponent* FleeStartRange;

	UPROPERTY(VisibleAnyWhere, Category = "Collision")
	class USphereComponent* FleeEndRange;

	//UPROPERTY(VisibleAnyWhere,Category= "Collision")
	//class USphereComponent* DetectStartRange;

	//UPROPERTY(VisibleAnyWhere, Category = "Collision")
	//class USphereComponent* DetectEndRange;
	//
	//UPROPERTY(VisibleAnyWhere, Category = "Collision")
	//class USphereComponent* AttackStatrRange;
	//
	//UPROPERTY(VisibleAnyWhere, Category = "Collision")
	//class USphereComponent* AttackEndRange;

	class ACCharacterPlayer* player;
	UPROPERTY(EditAnywhere, Category = VisualEffect)
	UParticleSystem* HittedParticle;
	//int hp;
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Offense) override;
	
	FVector  spawnpoint;
	FVector  targetLocation;
	FVector  direction;
	FVector  predirection;
	float sumDeltaTime;
	UPROPERTY(EditAnywhere, Category = Rotatespeed)
	float RotationSpeed;
	bool targetSet;

	float moveSpeed;
	FVector redirection;
	FVector redirection_L;
	FVector redirection_R;
	bool isredirection;
	UPROPERTY(EditAnyWhere, Category = "Montage")
	UAnimMontage* AM_HitReact;
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* AM_DeadReact;
	void SpawnItem();
	
	UPROPERTY(EditAnywhere, Category = Item)
	TSubclassOf<class AItemBase> Items[4];
private:
	void HitReact(const FVector& ImpactPoint);
	void DeadReact(const FVector& ImpactPoint);
	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* Attributes;
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;
	UAnimInstance* animInstance;
};
