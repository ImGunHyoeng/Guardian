// Fill out your copyright notice in the Description page of Project Settings.


#include "Particalble/ParticableBase.h"

// Sets default values
AParticableBase::AParticableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AParticableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParticableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

