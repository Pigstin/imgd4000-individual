// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameFramework/Controller.h>
#include "Boid.h"
#include <BoidController.generated.h>

/**
 * 
 */
UCLASS()
class BOIDS2_API ABoidController : public AActor
{

	GENERATED_BODY()

public:
	ABoidController();
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;


	void setupBoids();
	void moveBoids(float deltaTime);

	UPROPERTY(EditAnywhere, Category = "Boid config")
	TSubclassOf<ABoid> boidToSpawn;

	UPROPERTY(EditAnywhere, Category = "Boid config")
	int boidNum;

	UPROPERTY(EditAnywhere, Category = "Boid config")
	float boidDistanceFromEachOther;
	
	UPROPERTY(EditAnywhere, Category = "Boid config")
	float boidMaxSpeed;

	UPROPERTY(EditAnywhere, Category = "Boid config")
	float boidBoundDiscouragement;


	UPROPERTY(EditAnywhere, Category = "Boid config")
	FVector boidBound1;
	UPROPERTY(EditAnywhere, Category = "Boid config")
	FVector boidBound2;

	FVector minBound;
	FVector maxBound;

	TArray<ABoid*> BoidArr;

private: 
	FVector BoidRule1(int boidIndex);
	FVector BoidRule2(int boidIndex);
	FVector BoidRule3(int boidIndex);
	FVector BoidRule4(int boidIndex);
	FVector limitBoidSpeed(int boidIndex);

};
