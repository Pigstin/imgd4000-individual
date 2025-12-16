// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidController.h"
ABoidController::ABoidController() {
	// make sure this ticks every frame so boids move
	PrimaryActorTick.bCanEverTick = true;

}


void ABoidController::BeginPlay() {
	
	Super::BeginPlay();

	this->minBound = FVector(
		FMath::Min(this->boidBound1.X, this->boidBound2.X),
		FMath::Min(this->boidBound1.Y, this->boidBound2.Y),
		FMath::Min(this->boidBound1.Z, this->boidBound2.Z)
	);
	this->maxBound = FVector(
		FMath::Max(this->boidBound1.X, this->boidBound2.X),
		FMath::Max(this->boidBound1.Y, this->boidBound2.Y),
		FMath::Max(this->boidBound1.Z, this->boidBound2.Z)
	);

	UE_LOG(LogTemp, Log, TEXT("%s"), *this->minBound.ToCompactString());
	UE_LOG(LogTemp, Log, TEXT("%s"), *this->maxBound.ToCompactString());

	this->setupBoids();

}

void ABoidController::setupBoids() {
	for (int i = 0; i < boidNum; i++) {

		
		ABoid* boid = static_cast<ABoid*>(GetWorld()->SpawnActor(boidToSpawn.Get()));
		BoidArr.Add(boid);
		
		// random starting location
		float randX = FMath::FRandRange(this->minBound.X, this->maxBound.X);
		float randY = FMath::FRandRange(this->minBound.Y, this->maxBound.Y);
		float randZ = FMath::FRandRange(this->minBound.Z, this->maxBound.Z);
		boid->SetActorLocation(FVector(randX, randY, randZ));

		boid->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

	}
}

void ABoidController::Tick(float deltaTime) {
	//GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Green, FString::Printf(TEXT("%d"), this->BoidArr.Num()));
	this->moveBoids(deltaTime);
} 

void ABoidController::moveBoids(float deltaTime) {
	//GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Green, FString::Printf(TEXT("%f"), deltaTime));
	for (int i = 0; i < boidNum; i++) {
		//UE_LOG(LogTemp, Log, TEXT("%d"), i);

		FVector loc = this->BoidArr[i]->GetActorLocation();
		FVector vel = this->BoidArr[i]->velocity;


		vel += this->BoidRule1(i) + this->BoidRule2(i) + this->BoidRule3(i) + this->BoidRule4(i);
		this->limitBoidSpeed(i);
		loc += vel * deltaTime;

		this->BoidArr[i]->SetActorLocation(loc);
		this->BoidArr[i]->velocity = vel;
		
		//GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Green, FString::Printf(TEXT("%f"), deltaTime));
		//UE_LOG(LogTemp, Log, TEXT("%s"), *this->BoidArr[i]->GetActorLocation().ToCompactString());
		//UE_LOG(LogTemp, Log, TEXT("%s"), *this->BoidArr[i]->velocity.ToCompactString());

	}
}

// fly towards the center of mass of boids
FVector ABoidController::BoidRule1(int boidIndex) {
	FVector centerOfMass = FVector();

	for (int i = 0; i < boidNum; i++) {
		if (i == boidIndex) { continue; }
		centerOfMass += this->BoidArr[i]->GetActorLocation();

	}

	centerOfMass /= this->boidNum - 1;

	return (centerOfMass - this->BoidArr[boidIndex]->GetActorLocation()) / 100;
}

// stay away from other boids
FVector ABoidController::BoidRule2(int boidIndex) {
	FVector boidDisplacement = FVector();

	for (int i = 0; i < boidNum; i++) {
		if (i == boidIndex) { continue; }
		
		if ((
			this->BoidArr[i]->GetActorLocation() -
			this->BoidArr[boidIndex]->GetActorLocation()
			).SquaredLength() < FMath::Pow(this->boidDistanceFromEachOther, 2) ) {

				boidDisplacement -= (this->BoidArr[i]->GetActorLocation() - this->BoidArr[boidIndex]->GetActorLocation());

		}


	}

	return boidDisplacement;
} 

// matching velocity with nearby boids
FVector ABoidController::BoidRule3(int boidIndex) {
	FVector boidDisplacement = FVector();

	for (int i = 0; i < boidNum; i++) {
		if (i == boidIndex) { continue; }

		boidDisplacement += this->BoidArr[i]->velocity;
		
	}

	boidDisplacement /= this->boidNum - 1;

	return (boidDisplacement - this->BoidArr[boidIndex]->velocity) / 8;
} 

// stay within min and max bounds
FVector ABoidController::BoidRule4(int boidIndex) {
	FVector boidDisplacement = FVector();
	FVector boidPos = this->BoidArr[boidIndex]->GetActorLocation(); 

	if (boidPos.X < this->minBound.X) { boidDisplacement.X = boidBoundDiscouragement; }
	else if (boidPos.X > this->maxBound.X) { boidDisplacement.X = -boidBoundDiscouragement; }

	if (boidPos.Y < this->minBound.Y) { boidDisplacement.Y = boidBoundDiscouragement; }
	else if (boidPos.Y > this->maxBound.Y) { boidDisplacement.Y = -boidBoundDiscouragement; }

	if (boidPos.Z < this->minBound.Z) { boidDisplacement.Z = boidBoundDiscouragement; }
	else if (boidPos.Z > this->maxBound.Z) { boidDisplacement.Z = -boidBoundDiscouragement; }

	return boidDisplacement;
}

// limit speed
FVector ABoidController::limitBoidSpeed(int boidIndex) {
	FVector boidVel = this->BoidArr[boidIndex]->velocity; 

	if (boidVel.SquaredLength() > FMath::Pow(this->boidMaxSpeed, 2)) {
		boidVel = (boidVel / boidVel.Length()) * this->boidMaxSpeed;
	}
	
	return boidVel;
}