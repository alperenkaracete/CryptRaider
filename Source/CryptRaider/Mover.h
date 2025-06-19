// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();
	UPROPERTY (EditAnywhere, Category = "Activate")
	bool shouldMove;
	UPROPERTY (VisibleAnywhere, Category = "Interp Position")
	FVector startPosition;
	UPROPERTY (EditAnywhere, Category = "Interp Position")
	FVector endPosition;
	UPROPERTY (EditAnywhere, Category = "Interp Position")
	int moveTime = 5;
	void setShouldMove(bool move);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
