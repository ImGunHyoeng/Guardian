// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Hit\HitInterface.h"
#include "CMonsterBase.generated.h"

class UAttributeComponent;
class UHealthBarComponent;
class UMenuWidget;
UCLASS()
class CAIMAN_API ACMonsterBase : public ACharacter,public IHitInterface
{
	GENERATED_BODY()
	
		uint32 bIsAlredyDie : 1;
		float hp;
	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* Attributes;
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;
public:
	// Sets default values for this character's properties
	ACMonsterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void setHp(float _hp);
	UFUNCTION(BlueprintCallable)
	void SetWidgetVisible(bool input);
public:	
	// Called every frame

	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	float getHp();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	uint32 bIsLive : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bIsHeal : 1;
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Offense) override;
	
	UParticleSystem* GetParticle() { return HittedParticle; }
	UPROPERTY(EditAnywhere, Category = VisualEffect)
	UParticleSystem* HittedParticle;
	UPROPERTY(EditAnywhere, Category = VisualEffect)
	UParticleSystem* ParringParticle;
	UPROPERTY(EditAnywhere, Category = HittedSound)
	class USoundBase* ThunderSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Position)
	FVector RunDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Position)
	FVector StartPoint;
	//void ReceivePointDamage(float Damage,
	//	const class UDamageType* DamageType,
	//	FVector HitLocation,
	//	FVector HitNormal,
	//	class UPrimitiveComponent* HitComponent,
	//	FName BoneName,
	//	FVector ShotFromDirection,
	//	class AController* InstigatedBy,
	//	AActor* DamageCauser
	//) ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int healcount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bIsRunAwayDone : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bIsAttacking: 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bIsInC_AttackRange: 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bIsInL_AttackRange : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bIsInD_Range : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bIsGoHome : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bIsDetect : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bIsAttacked : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint32 bIsCoolTime: 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int attackType;

	//UPROPERTY(EditAnywhere, Category = "Widget")
	//TSubclassOf<UUserWidget> ClearClass;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget)
	//UMenuWidget* Clear;
	////UPROPERTY() //The class (could also be done in a local function for a one-time go)
	////	TSubclassOf<UUserWidget> Clear;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget)
	//	UMenuWidget* Clear;
	//UFUNCTION(BlueprintImplementableEvent)
	//void Clear();
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Montage)
		UAnimMontage* AM_Hited;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Montage)
		UAnimMontage* AM_Dead;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Montage)
		UAnimMontage* AM_Angry;

	virtual float InternalTakePointDamage(float Damage, struct FPointDamageEvent const& PointDamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
