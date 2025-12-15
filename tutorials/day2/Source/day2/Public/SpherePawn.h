// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <GameFramework/FloatingPawnMovement.h>
#include "InputActionValue.h"					// did this so it would compile 
#include "SpherePawn.generated.h"

UCLASS()
class DAY2_API ASpherePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpherePawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//U prefix denotes a class
	UPROPERTY(EditAnywhere) class UStaticMeshComponent* Mesh;

	void Move(const FInputActionValue& InputActionValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFloatingPawnMovement* PawnMovement;

};
