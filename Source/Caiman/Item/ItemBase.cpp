// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"
#include "Engine/DataTable.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;	
	static ConstructorHelpers::FObjectFinder<UDataTable> ItemDataObject(TEXT("/Game/DATABASE/DT_ItemTable.DT_ItemTable"));
	if (ItemDataObject.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("DataTable Succeed!"));
		Items = ItemDataObject.Object;
	}
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	FItemDataBase* ItemData = Items->FindRow<FItemDataBase>(Item.ItemID.RowName, FString(""));
	if (ItemData)
	{
		//UStaticMeshComponent* StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
		Mesh->SetStaticMesh(ItemData->Mesh);
		//Mesh = ItemData->Mesh;
	}
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

