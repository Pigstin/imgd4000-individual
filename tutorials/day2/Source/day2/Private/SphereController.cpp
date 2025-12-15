// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereController.h"
#include <SpherePawn.h>
#include "EnhancedInputComponent.h"

void ASphereController::BeginPlay()
{
	// Call the superclass method for BeginPlay() so Unreal knows to include this as part of the list of objects doing stuff
	Super::BeginPlay();

	//checkf makes sure the IMC and MoveAction are set in the Details pane in Unreal Editor. If not, it'll (intentionally) crash Unreal at this line.
	checkf(InputMappingContext, TEXT("InputMappingContext is not set in %s"), *GetNameSafe(this));
	checkf(MoveAction, TEXT("MoveAction is not set in %s"), *GetNameSafe(this));

	//Get a pointer to the EnhancedInputSubsystem
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	//Add the IMC to the EnhancedInputSubsystem
	if (EnhancedInputSubsystem) {
		EnhancedInputSubsystem->AddMappingContext(InputMappingContext, 0);
	}

}

//Set up player input
void ASphereController::SetupInputComponent()
{
	//Access super class to connect input
	Super::SetupInputComponent();

	//Get a pointer to the EnhancedInputComponent our PlayerController now has
	// Cast Checked ensures this is not a nullptr
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	//Bind the MoveAction to the Move method
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASphereController::Move);

}

//Passes input to the SpherePawn so that it moves itself
void ASphereController::Move(const FInputActionValue& InputActionValue)
{
	if (ASpherePawn* ControlPawn = GetPawn<ASpherePawn>())
	{
		//GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Green, FString(ControlPawn->GetName()));
		ControlPawn->Move(InputActionValue);
	}
}