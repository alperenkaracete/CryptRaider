// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
	public:
		UTriggerComponent();
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		UPROPERTY (EditAnywhere)
		FName acceptableTag;

		AActor* getAcceptableActor() const;

		UFUNCTION (BlueprintCallable)
		void setMover(UMover* NewMover);
	protected:
		virtual void BeginPlay() override;
		UMover* Mover;
};
