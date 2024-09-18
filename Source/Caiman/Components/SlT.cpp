// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SlT.h"
#include "SlateBasics.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ASlT::ASlT()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASlT::BeginPlay()
{
	Super::BeginPlay();
	Super::BeginPlay();
	TSharedRef<SVerticalBox> widget = SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
				.Content()
				[
					SNew(STextBlock)
						.Text(FText::FromString(TEXT("test")))
				]
		];
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	//PlayerController;
}

// Called every frame
void ASlT::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

