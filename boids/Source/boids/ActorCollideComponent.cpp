
#include "ActorCollideComponent.h"

// Sets default values for this component's properties
UActorCollideComponent::UActorCollideComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UActorCollideComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("begin"));

	AActor* actor = GetOwner();
	UStaticMeshComponent* cube = actor->FindComponentByClass<UStaticMeshComponent>();

	cube->OnComponentHit.AddDynamic(this, &UActorCollideComponent::OnActorHit);
}

// Called every frame
void UActorCollideComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//UE_LOG(LogTemp, Warning, TEXT("tick"));
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UActorCollideComponent::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	UE_LOG(LogTemp, Warning, TEXT("HIT!"));
}