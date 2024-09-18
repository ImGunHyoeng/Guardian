// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SLATETESTC.h"
#include "SlateBasics.h"
#include "Kismet/GameplayStatics.h"
// Sets default values for this component's properties
USLATETESTC::USLATETESTC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USLATETESTC::BeginPlay()
{
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

	//APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//PlayerController;
	//return widget;
	//GEngine->GameViewport->AddViewportWidgetForPlayer(getplayer)
	// ...
	
}


// Called every frame
void USLATETESTC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

