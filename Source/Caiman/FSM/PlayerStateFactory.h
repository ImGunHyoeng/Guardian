// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CCharacterPlayer.h"
#include "PlayerStateFactory.generated.h"

/**
 * 
 */
class UPlayerStateBase;
UCLASS()
class CAIMAN_API UPlayerStateFactory : public UObject
{
	GENERATED_BODY()


	//팩토리에서 변수생성해서 사용
	UPROPERTY()
	UPlayerStateBase* attack;
	UPROPERTY()
	UPlayerStateBase* chargeAttack;
	UPROPERTY()
	UPlayerStateBase* d_Idle;
	UPROPERTY()
	UPlayerStateBase* d_Walk;
	UPROPERTY()
	UPlayerStateBase* defenseless;
	UPROPERTY()
	UPlayerStateBase* drawing;
	UPROPERTY()
	UPlayerStateBase* grounded;
	UPROPERTY()
	UPlayerStateBase* hit;
	UPROPERTY()
	UPlayerStateBase* invincibility;
	UPROPERTY()
	UPlayerStateBase* jump;
	UPROPERTY()
	UPlayerStateBase* jumpattack;
	UPROPERTY()
	UPlayerStateBase* normal;
	UPROPERTY()
	UPlayerStateBase* parring;
	UPROPERTY()
	UPlayerStateBase* parringsuccess;
	UPROPERTY()
	UPlayerStateBase* s_idle;
	UPROPERTY()
	UPlayerStateBase* s_roll;
	UPROPERTY()
	UPlayerStateBase* s_run;
	UPROPERTY()
	UPlayerStateBase* s_walk;
	UPROPERTY()
	UPlayerStateBase* sheathing;
	UPROPERTY()
	UPlayerStateBase* superarmor;
	UPROPERTY()
	UPlayerStateBase* s_rest;
	UPROPERTY()
	UPlayerStateBase* d_rest;
	UPROPERTY()
	UPlayerStateBase* knockback;
	UPROPERTY()
	UPlayerStateBase* superchargeattack;



public:
	UPROPERTY()
	ACCharacterPlayer* context;
	void Set(ACCharacterPlayer* input);
	UPlayerStateFactory() {};
	UPlayerStateBase* CreateS_IDLE();
	UPlayerStateBase* CreateS_WALK();
	UPlayerStateBase* CreateS_RUN();
	UPlayerStateBase* CreateS_ROLL();
	UPlayerStateBase* CreateSHEATHING();
	UPlayerStateBase* CreatePARRINGSUCCESS();
	UPlayerStateBase* CreatePARRING();
	UPlayerStateBase* CreateJUMPATTACK();
	UPlayerStateBase* CreateJUMP();
	UPlayerStateBase* CreateGROUNDED();
	UPlayerStateBase* CreateDRAWING();
	UPlayerStateBase* CreateDEFENSELESS();
	UPlayerStateBase* CreateD_WALK();
	UPlayerStateBase* CreateD_IDLE();
	UPlayerStateBase* CreateCHARGINGATTACK();
	UPlayerStateBase* CreateATTACK();
	UPlayerStateBase* CreateHIT();
	UPlayerStateBase* CreateNORMAL();
	UPlayerStateBase* CreateINVINCIBILITY();
	UPlayerStateBase* CreateSUPERARMOR();
	UPlayerStateBase* CreateD_Rest();
	UPlayerStateBase* CreateS_Rest();
	UPlayerStateBase* CreateKNOCKBACK();
	UPlayerStateBase* CreateSUPERCHARGINGATTACK();
	~UPlayerStateFactory();
};
