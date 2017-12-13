// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	SetupInputComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
	/// Loof for attached Physics handle
	PhisicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhisicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not get UPhysicsHandleComponent from Grabber owner: %s!"), *GetOwner()->GetName())
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		/// Bind intput action
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Released);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Could not get component: %s"), *GetOwner()->GetName())
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab clicked"))

	// Line trace and see if we reach any actors with physics body collision set

	// if we hit something attach a physics handle
	// TODO attach phisics handle
}

void UGrabber::Released()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"))
	// TODO release physics handle
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotator;

	if (GetWorld())
	{
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotator
		);


		/// Draw a red, debug, trace
		FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotator.Vector() * m_reach);
	
		//DrawDebugLine(
		//	GetWorld(),
		//	PlayerViewPointLocation,
		//	LineTraceEnd,
		//	FColor(255,0,0),
		//	false,
		//	0.f,
		//	0,
		//	10.0f
		//);

		/// Line-trace(Ray-cast) out to reach distance
		FHitResult Hit;
		FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
		GetWorld()->LineTraceSingleByObjectType(
			OUT Hit,
			PlayerViewPointLocation,
			LineTraceEnd,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
			TraceParameters
		);

		/// See what we hit
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			FString HitActorName = HitActor->GetName();

			UE_LOG(LogTemp, Warning, TEXT("Hit actor name: %s"), *(HitActor->GetName()))
		}
	}
}

