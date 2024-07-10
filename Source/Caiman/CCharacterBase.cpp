// Fill out your copyright notice in the Description page of Project Settings.


#include "CCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ACCharacterBase::ACCharacterBase()
{
	//
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 400.0f;
	//CameraBoom->bUsePawnControlRotation = true;//캐릭터의 움직임에 따라서 돌아감.

	//Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);//스프링암의 소켓에다가 카메라를 입력해서 넣어둠
	//Camera->bUsePawnControlRotation = false;

	//매프레임마다 tick호출을 하겠다는 의미
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;//컨트롤러의 회전을 따라갈 것인지를 정하는 것
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//Capsule
	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("CCapsule"));

	//SkelatalMesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));//메시가 항상 위쪽에 90정도 띄어있기에  -90으로 위치를 맞추고 캐릭터와 방향이 -90정도로 화살표가 돌아가 있기에 이를 조절함.
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));//충돌 설정시에 profile의 이름을 설정하는 것.

	//CharacterMovement
	GetCharacterMovement()->bOrientRotationToMovement = true;//원하는 방향으로 캐릭터가 움직이는 것
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.f, 0.0f);//y축으로의 회전만 넣어서 Yaw회전을 기준으로 움직이도록 한 것이다.
	GetCharacterMovement()->JumpZVelocity = 500.0f;//점프력 설정
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;//걷는 최대 속도
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;//걷기 완화 속도

	//static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/KwangRosewood.KwangRosewood'"));
	//if (CharacterMeshRef.Object)
	//{
	//	GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	//}

	//static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnimRef(TEXT("/Game/Blueprints/Animation/KwangAniminstance.KwangAniminstance_C"));
	//if (CharacterAnimRef.Class)
	//{
	//	GetMesh()->SetAnimInstanceClass(CharacterAnimRef.Class);
	//}
	//cpp에서 초기화해서 하는 것이 아니라 블루프린트로 선언해서 사용해야함 (동기적 로딩,확장성)

}

// Called when the game starts or when spawned
void ACCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


