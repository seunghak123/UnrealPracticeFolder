// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
// Sets default values
ACharacterBase::ACharacterBase() : cameraCompo(nullptr) , springCompo(nullptr)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	cameraCompo = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	springCompo = CreateDefaultSubobject< USpringArmComponent>(TEXT("UserArms"));
	springCompo->SetupAttachment(GetCapsuleComponent());
	cameraCompo->SetupAttachment(springCompo);
	//InputSystem
	//�޽��� 1��?

}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	//APlayerController* playerContoller = Cast<APlayerController>(GetController());

	//if (playerContoller != nullptr)
	//{
	//	ULocalPlayer* userPlayer = playerContoller->GetLocalPlayer();

	//	if (userPlayer)
	//	{
	//		UEnhancedInputLocalPlayerSubsystem* inputSubSystem = userPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	//		if (inputSubSystem) 
	//		{
	//			inputSubSystem->AddMappingContext(inputMapping.LoadSynchronous(),0 );
	//		}
	//	}
	//	//userPlayer->
	//}
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//this->AddMovementInput()
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (inputComponent != nullptr) 
	{
		inputComponent->BindAction(moveAction.LoadSynchronous(),ETriggerEvent::Triggered,this, &ACharacterBase::Move);
		inputComponent->BindAction(ratationAction.LoadSynchronous(),ETriggerEvent::Triggered,this, &ACharacterBase::Rotation);
	}
}

void ACharacterBase::Move(const FInputActionInstance& _moveInstance)
{
	//UE_LOG(LogTemp, Warning, TEXT("Call"));
	//FVector2D targetVector = _moveInstance.GetValue().Get<FVector2D>();
	//if (targetVector.X != 0) 
	//{
	//	GetCharacterMovement()->AddInputVector(GetActorForwardVector() * targetVector.X);	
	//}

	//if (targetVector.Y != 0) 
	//{
	//	GetCharacterMovement()->AddInputVector(GetActorRightVector() * targetVector.Y);
	//}
}

void ACharacterBase::Rotation(const FInputActionInstance& _rotationInstance)
{
	//FVector2D targetVector = _rotationInstance.GetValue().Get<FVector2D>();

	//AddControllerYawInput(targetVector.X);

	//FRotator targetRotator = springCompo->GetRelativeRotation();
	
	//springCompo->SetRelativeRotation(FVector(0, 0, targetVector.Y + targetRotator.Yaw).ToOrientationRotator());
	//cameraCompo->AddControllerPitchInput(targetVector.Y);
	
}

