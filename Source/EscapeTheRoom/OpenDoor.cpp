// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeTheRoom.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
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
	
	owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	owner->SetActorRotation(FRotator(0.0f, DoorOpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (PressurePLate->IsOverlappingActor(ActorThatOpens)) 
	{
		OpenDoor();
		lastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	float deltaTime = GetWorld()->GetTimeSeconds() - lastDoorOpenTime;
	
	if (lastDoorOpenTime != 0.0 && deltaTime >= DoorCloseDelay) 
	{
		CloseDoor();
	}
	
}

