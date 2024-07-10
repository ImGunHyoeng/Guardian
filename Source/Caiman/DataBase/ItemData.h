// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"

UENUM(BlueprintType)
enum class EItemTypes : uint8 
{ Weapon UMETA(DisplayName = "Weapon"),
  Armor UMETA(DisplayName = "Armor"), 
  Item UMETA(DisplayName = "Item") };

USTRUCT(BlueprintType)
struct FItemDataBase : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Data")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UTexture2D * Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int StackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UStaticMesh* Mesh ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Power;
};
USTRUCT(BlueprintType)
struct FItemSlot : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FDataTableRowHandle ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int Quantity=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	EItemTypes type;

};

USTRUCT(BlueprintType)
struct FAllItem : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FItemSlot> Swords;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FItemSlot> Armors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	TArray<FItemSlot> Items;
};
UCLASS()
class CAIMAN_API AItemData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
