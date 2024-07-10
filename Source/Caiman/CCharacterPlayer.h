// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CCharacterBase.h"
#include "GameFramework/character.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Hit\HitInterface.h"
#include "FSM/PlayerStateBase.h"
#include "CCharacterPlayer.generated.h"

UENUM(BlueprintType)
enum class ECharacterState :uint8
{
	S_IDLE,
	S_WALK,
	S_RUN,
	JUMP,
	GROUNDED,
	S_ROLL,
	D_IDLE,
	D_WALK,
	D_ROLL,
	JUMPATTACK,
	DEFENSELESS,
	PARRGING,
	ATTACK
};
/**
 * 
 */
class UPlayerStateFactory;
class ACMyWeapon;
class UAttributeComponent;
class UHealthBarComponent;
class UPlayerOverlay;
class UMenuWidget;
class UInventoryComponent;
UCLASS()
class CAIMAN_API ACCharacterPlayer : public ACCharacterBase,public IHitInterface
{
	GENERATED_BODY()
public:	
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Camera)
	TObjectPtr<class USpringArmComponent>CameraBoom;//스프링암

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Camera)
		TObjectPtr<class UCameraComponent>Camera;//카메라

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Naiagra)
	TObjectPtr<class UNiagaraSystem> NiagaraEffect;


	ACCharacterPlayer();
	~ACCharacterPlayer();
	void AttackCheck();
	virtual void update();
	virtual void updateInput();
	//void changeState(ECharacterState inState);
	
	
	UPlayerStateBase* getCurState() { return curState; }
	void setCurState(UPlayerStateBase* state) { curState = state; }
	APlayerController* getPlayerController();
	void SimulateSpaceKeyPress(const FName name);
	void OnReleaseKey();

	const FInputActionValue GetMoveInputActionValue();
	const FInputActionValue GetLookInputActionValue();
	FORCEINLINE	UAnimMontage* GetDrawMontage() { return AM_Draw; }
	FORCEINLINE UAnimMontage* GetSheathMontage() { return AM_Sheath; }
	FORCEINLINE UAnimMontage* GetAttackMontage() { return AM_Attack; }
	FORCEINLINE UAnimMontage* GetHittedMontage() { return AM_Hitted; }
	FORCEINLINE UAnimMontage* GetRollMontage() { return AM_Roll; }
	FORCEINLINE UAnimMontage* GetParringMontage() { return AM_Parring; }
	FORCEINLINE UAnimMontage* GetChargeAttackMontage() { return AM_ChargeAttack; }
	FORCEINLINE UAnimMontage* GetDefenseLessMontage() { return AM_DefenseLess; }
	FORCEINLINE UAnimMontage* GetS_RestMontage() { return AM_S_Rest; }
	FORCEINLINE UAnimMontage* GetD_RestMontage() { return AM_D_Rest; }

	//FORCEINLINE UKwangAnimInstance * GetKwangAnim() { return Cast<UKwangAnimInstance>(GetMesh()->GetAnimInstance()); }

	//UFUNCTION(BlueprintCallable)
	UPlayerStateBase* GetCurPlayerState();

	//기다리는 시간 계산
	FORCEINLINE	const float GetWaitFrame() { return WaitFrame; }
	FORCEINLINE void SetWaitFrame(float input) { WaitFrame = input; }
	void WaitFramePassing();

	class UKwangAnimInstance* getAnimInstance();
	const TObjectPtr<class ACMyWeapon> GetWeapon();
	void SetKey(FKey _key);

	//공통적인 행동(보고,움직이고,칼 빼기)
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void QuickRotate(const FInputActionValue& Value);
	void StopMove();
	void Draw();
	void NoAnimDraw();
	void Sheath();
	void NoAnimSheath();

	//particle set
	UParticleSystem* GetHittedParticle() { return HittedParticle; }
	//UParticleSystem* GetParringParticle() { return ParringParticle; }
	//UParticleSystem* GetJumpAttackParticle() { return JumpAttackParticle; }
	//UParticleSystem* GetAttackParticle() { return AttackParticle; }
	//UParticleSystem* GetNormalAttackParticle() { return NormalAttackParticle; }
	//void SetAttackParticle(UParticleSystem* set) { AttackParticle = set; }

	virtual void GetHit_Implementation(const FVector& ImpactPoint,AActor* Offense) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void SetRagdollPhysics();

	FORCEINLINE void SetParring(bool input) { bIsParring = input; }
	FORCEINLINE bool GetParring() { return bIsParring; }

	FORCEINLINE bool GetParringEnd() { return bIsParringEnd; }
	FORCEINLINE void SetParringEnd(bool input) { bIsParringEnd = input; }
	FORCEINLINE bool GetParringSuccessEnd() { return bIsParringSuccessEnd; }
	FORCEINLINE void SetParringSuccessEnd(bool input) { bIsParringSuccessEnd = input; }

	FORCEINLINE bool GetAttacked() { return bIsAttacked; }
	FORCEINLINE void SetAttacked(bool input) { bIsAttacked = input; }
	FORCEINLINE bool GetSheath() { return bIsSheath; }
	FORCEINLINE void SetSheath(bool input) { bIsSheath = input; }

	FORCEINLINE bool GetDefenseLess() { return bIsDefenseLess; }
	FORCEINLINE void SetDefenseLess(bool input) { bIsDefenseLess = input; }

	FORCEINLINE bool IsAttack() { return bIsAttack; }
	FORCEINLINE void SetAttack(bool input) { bIsAttack = input; }


	//속성
	FORCEINLINE UAttributeComponent *GetAttribute() { return Attributes; }
	FORCEINLINE UPlayerOverlay *GetHUD() { return PlayerOverlay; }
	FORCEINLINE void SetUsingStamina(bool input) { bIsUsingStamina = input; }
	
	bool HasEnoughStamina(float Cost);
	UFUNCTION(BlueprintImplementableEvent)
	void SetNaiagra();
	UFUNCTION(BlueprintImplementableEvent)
	void DeActiveNaiagra();

	UFUNCTION()
	void EnemyDie();
	UPROPERTY(BlueprintReadOnly)
	uint32 bIsDie : 1;

protected:

	FKey key;
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* PlayerContext;
	//매핑 텍스트

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> DrawAction;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Input)
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Input)
	UInputAction* RollAction;
	
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Input)
	UInputAction* InventoryAction;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Input)
	UInputAction* InteractionAction;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Input)
	TObjectPtr<class UInputAction> AttackAction;

	//몽타주

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Montage)
	UAnimMontage* AM_Draw;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Montage)
	UAnimMontage* AM_Sheath;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Montage)
	UAnimMontage* AM_Attack;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Montage)
	UAnimMontage* AM_Roll;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Montage)
	UAnimMontage* AM_Hitted;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Montage)
	UAnimMontage* AM_Parring;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Montage)
	UAnimMontage* AM_ChargeAttack;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Montage)
	UAnimMontage* AM_DefenseLess;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Montage)
	UAnimMontage* AM_D_Rest;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Montage)
	UAnimMontage* AM_S_Rest;


	//UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = Input)
	//UInputAction* JumpAction;*/
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;



	//void Move(const FInputActionValue& Value);


	//void Roll(const FInputActionValue& Value);
	//void Run();
	//void Walk();
	//void GoPrevious();
	//void GoWalk();
	//void GoIdle();
	//virtual void Jump() override;
	//void Landing(); 
	//void setPreviousState();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//void JumpAttack();
	//void Attack();
	//void Roll();

	//
	//void ComboAttack();





	float moveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaitFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bIsCombo : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bIsAttacked : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bIsParring : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint32 bIsParringEnd : 1;

	uint32 bIsParringSuccessEnd : 1;
	uint32 bIsSheath : 1;
	uint32 bIsAttack : 1;
	uint32 bIsDefenseLess : 1;
	uint32 bIsUsingStamina : 1;


	ACMyWeapon* Weapon;

	TObjectPtr<class UEnhancedInputComponent> EnhancedInputComponent;
	APlayerController* PlayerController;
	TArray<FEnhancedActionKeyMapping> KeyMappingArray;



	struct FEnhancedInputActionValueBinding const* MoveActionBinding;
	struct FEnhancedInputActionValueBinding const* LookActionBinding;

	UPROPERTY(EditAnywhere, Category = VisualEffect)
	UParticleSystem* HittedParticle;
	/*UPROPERTY(EditAnywhere, Category = VisualEffect)
	UParticleSystem* ParringParticle;*/
	UPROPERTY(EditAnywhere, Category = HittedSound)
	class USoundBase* HittedSound;

	//UPROPERTY(EditAnywhere, Category = VisualEffect)
	//UParticleSystem* JumpAttackParticle;
	//UPROPERTY(EditAnywhere, Category = VisualEffect)
	//UParticleSystem* NormalAttackParticle;
	//UPROPERTY(EditAnywhere, Category = VisualEffect)
	//UParticleSystem* AttackParticle;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TSubclassOf<ACMyWeapon> MyWeapon;

	
	//UPROPERTY() //The class (could also be done in a local function for a one-time go)
	//	TSubclassOf<UUserWidget> Restart;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> RestartClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget)
	UMenuWidget* Restart;
	
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> ClearClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget)
	UMenuWidget* Clear;

	//UFUNCTION(BlueprintImplementableEvent)
	//void Restart();
	UPlayerStateFactory* stateFactory;

	


private:
	//컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	UAttributeComponent* Attributes;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	UInventoryComponent* InventoryWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	UHealthBarComponent* HealthBarWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	UPlayerOverlay* PlayerOverlay;
	UPlayerStateBase* curState;

	void InitializePlayerOverlay();
};
