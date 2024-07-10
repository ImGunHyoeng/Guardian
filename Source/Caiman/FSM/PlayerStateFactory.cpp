// Fill out your copyright notice in the Description page of Project Settings.
#include "FSM/PlayerStateFactory.h"
#include "FSM/OBJECT_STATE/OFSMCollection.h"
#include "FSM/PlayerStateBase.h"
#include "CCharacterPlayer.h"
void UPlayerStateFactory::Set(ACCharacterPlayer* input)
{
	context = input;
	attack = NULL;
	chargeAttack = NULL;
	d_Idle = NULL;
	d_Walk = NULL;
	defenseless = NULL;
	drawing = NULL;
	grounded = NULL;
	hit = NULL;
	drawing = NULL;
	invincibility = NULL;
	jump = NULL;
	jumpattack = NULL;
	normal = NULL;
	parring = NULL;
	parringsuccess = NULL;
	s_idle = NULL;
	s_roll = NULL;
	s_run = NULL;
	s_walk = NULL;
	sheathing = NULL;
	superarmor = NULL;
	s_rest = NULL;
	d_rest = NULL;
	knockback = NULL;
	superchargeattack = NULL;

}

UPlayerStateFactory::~UPlayerStateFactory()
{
	/*if (attack)
		attack->Destroy();
	if (chargeAttack)
		chargeAttack->Destroy();
	if (d_Idle)
		d_Idle->Destroy();
	if (d_Walk)
		d_Walk->Destroy();
	if (defenseless)
		defenseless->Destroy();
	if (drawing)
		drawing->Destroy();
	if (grounded)
		grounded->Destroy();
	if (hit)
		hit->Destroy();
	if (drawing)
		drawing->Destroy();
	if (invincibility)
		invincibility->Destroy();
	if (jump)
		jump->Destroy();
	if (jumpattack)
		jumpattack->Destroy();
	if (normal)
		normal->Destroy();
	if (parring)
		parring->Destroy();
	if (parringsuccess)
		parringsuccess->Destroy();
	if (s_idle)
		s_idle->Destroy();
	if (s_roll)
		s_roll->Destroy();
	if (s_run)
		s_run->Destroy();
	if (s_walk)
		s_walk->Destroy();
	if (sheathing)
		sheathing->Destroy();
	if (superarmor)
		superarmor->Destroy();
	if (s_rest)
		s_rest->Destroy();
	if (d_rest)
		d_rest->Destroy();
	if (knockback)
		knockback->Destroy();
	if (superchargeattack)
		superchargeattack->Destroy();*/

}

UPlayerStateBase* UPlayerStateFactory::CreateS_IDLE()
{
	if (s_idle)
		if (s_idle->GetName()!="None")
			return s_idle;
	UPlayerStateBase* temp = NewObject<US_IDLE_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	s_idle = temp;
	return s_idle;
}

UPlayerStateBase* UPlayerStateFactory::CreateD_IDLE()
{
	if (d_Idle)
		if (d_Idle->GetName() != "None")
			return d_Idle;
	UPlayerStateBase* temp = NewObject<UD_IDLE_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	d_Idle = temp;
	return d_Idle;
}

UPlayerStateBase* UPlayerStateFactory::CreateS_WALK()
{
	if (s_walk)
		if (s_walk->GetName() != "None")
			return s_walk;
	UPlayerStateBase* temp = NewObject<US_WALK_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	s_walk = temp;
	return s_walk;
}

UPlayerStateBase* UPlayerStateFactory::CreateS_RUN()
{
	if (s_run)
		if (s_run->GetName() != "None")
			return s_run;
	UPlayerStateBase* temp = NewObject<US_RUN_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	s_run = temp;
	return s_run;
}

UPlayerStateBase* UPlayerStateFactory::CreateS_ROLL()
{
	if (s_roll)
		if (s_roll->GetName() != "None")
			return s_roll;
	UPlayerStateBase* temp = NewObject<US_ROLL_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	s_roll = temp;
	return s_roll;
}

UPlayerStateBase* UPlayerStateFactory::CreateSHEATHING()
{
	if (sheathing)
		if (sheathing->GetName() != "None")
			return sheathing;
	UPlayerStateBase* temp = NewObject<USHEATHING_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	sheathing = temp;
	return sheathing;
}

UPlayerStateBase* UPlayerStateFactory::CreatePARRINGSUCCESS()
{
	if (parringsuccess)
		if (parringsuccess->GetName() != "None")
			return parringsuccess;
	UPlayerStateBase* temp = NewObject<UPARRINGSUCCESS_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	parringsuccess = temp;
	return parringsuccess;
}

UPlayerStateBase* UPlayerStateFactory::CreatePARRING()
{
	if (parring)
		if (parring->GetName() != "None")
			return parring;
	UPlayerStateBase* temp = NewObject<UPARRING_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	parring = temp;
	return parring;
}

UPlayerStateBase* UPlayerStateFactory::CreateJUMPATTACK()
{
	if (jumpattack)
		if (jumpattack->GetName() != "None")
			return jumpattack;
	UPlayerStateBase* temp = NewObject<UJUMPATTACK_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	jumpattack = temp;
	return jumpattack;
}

UPlayerStateBase* UPlayerStateFactory::CreateJUMP()
{
	if (jump)
		if (jump->GetName() != "None")
			return jump;
	UPlayerStateBase* temp = NewObject<UJUMP_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	jump = temp;
	return jump;
}

UPlayerStateBase* UPlayerStateFactory::CreateGROUNDED()
{
	if (grounded)
		if (grounded->GetName() != "None")
			return grounded;
	UPlayerStateBase* temp = NewObject<UGROUNDED_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	grounded = temp;
	return grounded;
}

UPlayerStateBase* UPlayerStateFactory::CreateDRAWING()
{
	if (drawing)
		if (drawing->GetName() != "None")
			return drawing;
	UPlayerStateBase* temp = NewObject<UDRAWING_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	drawing = temp;
	return drawing;
}

UPlayerStateBase* UPlayerStateFactory::CreateDEFENSELESS()
{
	if (defenseless)
		if (defenseless->GetName() != "None")
			return defenseless;
	UPlayerStateBase* temp = NewObject<UDEFENSELESS_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	defenseless = temp;
	return defenseless;
}



UPlayerStateBase* UPlayerStateFactory::CreateD_WALK()
{
	if (d_Walk)
		if (d_Walk->GetName() != "None")
			return d_Walk;
	UPlayerStateBase* temp = NewObject<UD_WALK_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	d_Walk = temp;
	return d_Walk;
}

UPlayerStateBase* UPlayerStateFactory::CreateCHARGINGATTACK()
{
	if (chargeAttack)
		if (chargeAttack->GetName() != "None")
			return chargeAttack;
	UPlayerStateBase* temp = NewObject<UCHARGINGATTACK_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	chargeAttack = temp;
	return chargeAttack;
}

UPlayerStateBase* UPlayerStateFactory::CreateATTACK()
{
	if (attack)
		if (attack->GetName() != "None")
			return attack;
	UPlayerStateBase* temp = NewObject<UATTACK_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	attack = temp;
	return attack;
}

UPlayerStateBase* UPlayerStateFactory::CreateHIT()
{
	if (hit)
		if (hit->GetName() != "None")
			return hit;
	UPlayerStateBase* temp = NewObject<UHIT_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot(true);
	temp->AddToRoot();
	hit = temp;
	return hit;
}

UPlayerStateBase* UPlayerStateFactory::CreateNORMAL()
{
	if (normal)
		if (normal->GetName() != "None")
			return normal;
	UPlayerStateBase* temp = NewObject<UNORMAL_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot(true);
	temp->AddToRoot();
	normal = temp;
	return normal;
}

UPlayerStateBase* UPlayerStateFactory::CreateINVINCIBILITY()
{
	if (invincibility)
		if (invincibility->GetName() != "None")
			return invincibility;
	UPlayerStateBase* temp = NewObject<UINVINCIBILITY_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot(true);
	temp->AddToRoot();
	invincibility = temp;
	return invincibility;
}

UPlayerStateBase* UPlayerStateFactory::CreateSUPERARMOR()
{
	if (superarmor)
		if (superarmor->GetName() != "None")
			return superarmor;
	UPlayerStateBase* temp = NewObject<USUPERARMOR_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot(true);
	temp->AddToRoot();
	superarmor = temp;
	return superarmor;
}

UPlayerStateBase* UPlayerStateFactory::CreateD_Rest()
{
	if (d_rest)
		if (d_rest->GetName() != "None")
			return d_rest;
	UPlayerStateBase* temp = NewObject<UD_REST_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	d_rest = temp;
	return d_rest;
}

UPlayerStateBase* UPlayerStateFactory::CreateS_Rest()
{
	if (s_rest)
		if (s_rest->GetName() != "None")
			return s_rest;
	UPlayerStateBase* temp = NewObject<US_REST_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	s_rest = temp;
	return s_rest;
}

UPlayerStateBase* UPlayerStateFactory::CreateKNOCKBACK()
{
	if (knockback)
		if (knockback->GetName() != "None")
			return knockback;
	UPlayerStateBase* temp = NewObject<UKNOCKBACK_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	knockback = temp;
	return knockback;
}

UPlayerStateBase* UPlayerStateFactory::CreateSUPERCHARGINGATTACK()
{
	if (superchargeattack)
		if (superchargeattack->GetName() != "None")
			return superchargeattack;
	UPlayerStateBase* temp = NewObject<USUPERCHARGINGATTACK_O>();
	temp->SetInitalProperty(context, this);
	temp->SetRoot();
	temp->AddToRoot();
	superchargeattack = temp;
	return superchargeattack;
}
