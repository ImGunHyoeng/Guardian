// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "CMyWeapon.h"
#include "CTraceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CAIMAN_API UCTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCTraceComponent();

protected:
	// Called when the game starts
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* WeaponMesh;
	uint32 IsActive : 1;

	FVector start;
	FVector end;
	FVector dir;
	TArray<FHitResult> outResults;
	TArray<AActor*> attackObj;
	FCollisionShape mySphere;
	FColor color;
	void TsetActive(bool condition = true) { IsActive = condition; };
	class ACCharacterPlayer* player;
	class ACMyWeapon* Weapon;
	class UAttributeComponent* Attributes;
};
