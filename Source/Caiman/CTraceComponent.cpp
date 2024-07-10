// Fill out your copyright notice in the Description page of Project Settings.


#include "CTraceComponent.h"
#include "CMonsterBase.h"
#include "Kismet/GameplayStatics.h"
#include "Item/CMyWeapon.h"
#include "EngineUtils.h"
#include "Hit/HitInterface.h"
#include "CCharacterPlayer.h"
#include "Particalble\ParticableBase.h"
#include "Hit/HitInterface.h"
#include "Components/AttributeComponent.h"
// Sets default values for this component's properties
UCTraceComponent::UCTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}







void UCTraceComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
}

void UCTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	Weapon = Cast<ACMyWeapon>(GetOwner());
	player= Cast<ACCharacterPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Attributes = player->GetAttribute();
}

// Called every frame
void UCTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//if (Weapon)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Weapon"));
	//}
	//if (player)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("PlayerYes"));
	//}
	if (!WeaponMesh)
		return;
	if (!IsActive)
	{
		if(attackObj.Num()==0)
			return;
		attackObj.Reset();
		return;
	}
	attackObj.Add(GetOwner()->GetOwner());
	start = WeaponMesh->GetSocketLocation(FName("Start"));
	end = WeaponMesh->GetSocketLocation(FName("End"));
	dir = end - start;
	//Dir.Size();
	UE_LOG(LogTemp, Warning, TEXT("StartPosition: X: %.2f, Y: %.2f, Z: %.2f"), start.X, start.Y, start.Z);
	UE_LOG(LogTemp, Warning, TEXT("EndPosition: X: %.2f, Y: %.2f, Z: %.2f"), end.X, end.Y, end.Z);
	
	//UE_LOG(LogTemp, Warning,TEXT("End:%s"), *end.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Start:%s"), *start.ToString());
	//if (IsActive)
	
	mySphere = FCollisionShape::MakeSphere(10);
	GetWorld()->SweepMultiByChannel(outResults, start, end, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel1, mySphere);
	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f);
	color = outResults.IsEmpty() ? FColor::Red : FColor::Green;
	//if(!outResults.IsEmpty())
	//DrawDebugCapsule(GetWorld(),(start+end)/2, dir.Size()*0.5+10,10, FRotationMatrix::MakeFromZ(dir).ToQuat(),color, false, 2.0f);

	for (const auto & result : outResults)
	{
		if (Cast<AParticableBase>(result.GetActor()))
		{
			//ACCharacterPlayer* player = Cast<ACCharacterPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
			if (player)
			{
				//ACMyWeapon* Weapon = Cast<ACMyWeapon>(WeaponMesh->GetOwner());
				if (Weapon&& Weapon->GetWorld())
				{
					//result.ImpactPoint;
					//DrawDebugSphere(GetWorld(), result.ImpactPoint, 12, 16, FColor::Red, false, 10);
					DrawDebugSphere(GetWorld(), result.GetActor()->GetActorLocation(), 200, 16, FColor::Red, false, 10);
					//UE_LOG(LogTemp, Warning, TEXT("%f"),result.ImpactPoint.X);
					UE_LOG(LogTemp, Warning, TEXT("Position: X: %.2f, Y: %.2f, Z: %.2f"), result.ImpactPoint.X, result.ImpactPoint.Y, result.ImpactPoint.Z);
					UParticleSystemComponent*temp =UGameplayStatics::SpawnEmitterAtLocation(Weapon->GetWorld(), Weapon->GetHitParticle(),FTransform(FRotator(0,0,0), result.ImpactPoint, FVector(1, 1, 1)));
					if (nullptr == Weapon->GetHitParticle())
					{
						UE_LOG(LogTemp, Warning, TEXT("Particle No"));
					}
					if (temp == nullptr)
					{
						UE_LOG(LogTemp, Warning, TEXT("No work"));
					}

				}
				attackObj.Add(result.GetActor());
			}
		}
		//AActor* tempa;
		//tempa = WeaponMesh->GetOwner();
		////result.GetActor();
		
		//ACMyWeapon* temp= Cast<ACMyWeapon>(WeaponMesh->GetOwner());
		IHitInterface* monster= Cast<IHitInterface>(result.GetActor());
		/*if (!IsValid(monster) || temp->getDamage() == 0)
			return;
		if (monster->getHp() <= 0)
			return;*/
		if (!monster)
			return;
		if (attackObj.Contains<AActor*>(result.GetActor()))
			return;
		attackObj.Add(result.GetActor());
		UGameplayStatics::ApplyPointDamage(result.GetActor(), Attributes->GetPower(), result.ImpactNormal, result, GetWorld()->GetFirstPlayerController(), GetOwner(), nullptr);
		IHitInterface* Hit=Cast<IHitInterface>(result.GetActor());
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),player)
		if (Hit)
		{
			Hit->Execute_GetHit(result.GetActor(), result.ImpactPoint, GetOwner());
		}
	}
	

}

