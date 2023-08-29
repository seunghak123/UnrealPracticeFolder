// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "EngineMinimal.h"
#include "InputMappingContext.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class FIRSTPROJECT_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Component")
	UCameraComponent* cameraCompo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* springCompo;

	UPROPERTY(EditAnywhere, Category = "parameter")
	FVector2D moveVector;

#pragma region Action
	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> inputMapping;	

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> ratationAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputAction> moveAction;
#pragma endregion Action

public:
	// Sets default values for this character's properties
	ACharacterBase();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private :
	void Move(const FInputActionInstance& _moveInstance);
	void Rotation(const FInputActionInstance& _rotationInstance);
};
