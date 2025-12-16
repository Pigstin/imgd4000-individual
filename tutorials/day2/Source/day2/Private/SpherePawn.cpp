// Fill out your copyright notice in the Description page of Project Settings.


#include "SpherePawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "InputActionValue.h"
#include "SphereController.h"

// Sets default values
ASpherePawn::ASpherePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	Mesh->SetStaticMesh(SphereMeshAsset.Object);

	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ASpherePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpherePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpherePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASpherePawn::Move(const FInputActionValue& InputActionValue)
{

	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	//Get control rotation
	const FRotator ControlRotation = GetControlRotation();

	//Isolate the yaw
	const FRotator YawRotation(0, ControlRotation.Yaw, 0);
	//Get forward vector	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//Get right vector
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);



	//Move the character
	//GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Green, FString(Mesh->GetName()));
	//GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Green, FString(InputAxisVector.ToString()));
	//GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Green, FString(InputActionValue.Get<FVector3d>().ToString()));

	if (Mesh)
	{	
		AddMovementInput(ForwardDirection, InputAxisVector.Y);
		AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

