// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
	: ActorThatOpens(0l)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

}

void UOpenDoor::OpenDoor(bool open)
{
	// Find the owning actor
	AActor* Owner = GetOwner();

	// create a rotator
	FRotator NewRotation;
	if (open)
		NewRotation = FRotator(0.0f, OpenAngle, 0.0f);
	else
		NewRotation = FRotator(0.0f, 0.0f, 0.0f);

	// Set the door rotation
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetWorld() && !ActorThatOpens)
	{
		ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
	// ...
	//if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	//{
	if (ActorThatOpens)
	{
		bool overlapping = PressurePlate->IsOverlappingActor(ActorThatOpens);
		OpenDoor(overlapping);
	}
	//}

}

