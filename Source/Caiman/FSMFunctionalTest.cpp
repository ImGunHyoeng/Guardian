// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMFunctionalTest.h"
//#include "CCharacterPlayer.h"
//#include "Kismet/KismetSystemLibrary.h"
//#include "Kismet/GameplayStatics.h"

AFSMFunctionalTest::AFSMFunctionalTest()
{
	TimeLimit = 8.f;
	//DistanceThresh 거리 계산 액터가 움직일 수 있는 거리 제한
}

void AFSMFunctionalTest::BeginPlay()
{
	Super::BeginPlay();
	//controller = GetWorld()->GetFirstPlayerController();
	//if (controller)
	//{
	//	Player = CastChecked<ACCharacterPlayer>(controller->GetPawn());
	//	if (Player)
	//	{
	//		Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer());

	//		PlayerInput = Subsystem->GetPlayerInput();

	//		//InputAction = Player->getInputAction(TEXT("Jump"));
	//		bactivateFireInputAction = true;
	//	}
	//	else
	//	{
	//		FinishTest(EFunctionalTestResult::Failed, FString("Controller Null"));
	//		UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
	//	}
	//}
	//else
	//{
	//	FinishTest(EFunctionalTestResult::Failed, FString("Null Player Character Reference Pointer"));
	//	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
	//}
}

void AFSMFunctionalTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (bactivateFireInputAction)
	{
		Player->SetKey(EKeys::SpaceBar);
		Player->SimulateSpaceKeyPress(FName("Jump"));
		bactivateFireInputAction = false;
	}
	
	if (Cast<JUMP>(Player->GetCurPlayerState()))
	{
		LogMessage(FString("Jump is well"));
		return;
	}
	if (Cast<GROUNDED>(Player->GetCurPlayerState()))
	{
		Player->SetKey(EKeys::W);
		Player->SimulateSpaceKeyPress(FName("Move"));
		return;
	}
	

	if (Cast<S_WALK>(Player->GetCurPlayerState()))
	{
		LogMessage(FString("Walk is well"));
		Player->SetKey(EKeys::W);
		Player->SimulateSpaceKeyPress(FName("Move"));
		Player->SetKey(EKeys::LeftShift);
		Player->SimulateSpaceKeyPress(FName("Run"));
		return;
	}

	if (Cast<S_RUN>(Player->GetCurPlayerState()))
	{
		LogMessage(FString("Run is well"));
		Player->SetKey(EKeys::R);
		Player->SimulateSpaceKeyPress(FName("Draw"));
		return;
	}

	if (Cast<D_IDLE>(Player->GetCurPlayerState()))
	{
	
		LogMessage(FString("Draw is well"));
		Player->SetKey(EKeys::LeftMouseButton);
		Player->SimulateSpaceKeyPress(FName("Attack"));
		return;
	}

	if (Cast<ATTACK>(Player->GetCurPlayerState()))
	{
		LogMessage(FString("Attack is well"));
		FinishTest(EFunctionalTestResult::Succeeded, FString("FSM work well"));
		UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
		return;
	}*/



}
