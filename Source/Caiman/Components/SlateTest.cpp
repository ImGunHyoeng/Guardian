
// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/SlateTest.h"
#include "SlateBasics.h"
#include "Kismet/GameplayStatics.h"

SlateTest::SlateTest()
{
}

SlateTest::~SlateTest()
{
}

void SlateTest::Create()
{
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

	//return widget;
	//GEngine->GameViewport->AddViewportWidgetForPlayer(getplayer)
}
