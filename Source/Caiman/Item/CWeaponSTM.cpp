// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/CWeaponSTM.h"
#include "CTraceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ACWeaponSTM::ACWeaponSTM()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;										
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	trace = CreateDefaultSubobject<UCTraceComponent>(FName("TRACE"));
}

// Called when the game starts or when spawned
void ACWeaponSTM::BeginPlay()
{
	Super::BeginPlay();
	//trace->WeaponMesh = Mesh;
	Power = 10.0f;
}

// Called every frame
void ACWeaponSTM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

