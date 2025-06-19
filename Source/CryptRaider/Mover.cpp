// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMover::setShouldMove(bool move)
{
	shouldMove = move;
}

// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	// ...
	startPosition = GetOwner()->GetActorLocation();
	endPosition = startPosition;
	endPosition.Z -= 600;
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	AActor *Owner = GetOwner();
	float speed = FVector::Distance(startPosition,endPosition) / moveTime;

	FVector currentPosition = Owner->GetActorLocation();
	if (shouldMove){
		FVector newLocation = FMath::VInterpConstantTo(currentPosition,endPosition,DeltaTime,speed);
		Owner->SetActorLocation(newLocation);
	}

}

