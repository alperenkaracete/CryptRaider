// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp,Display,TEXT("TriggerComponent heeeeeeeeeeeey"));

    
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    AActor *foundedActor = getAcceptableActor();
    if (foundedActor!=nullptr && !foundedActor->ActorHasTag("Holding")){
        UPrimitiveComponent* rootComponent = Cast<UPrimitiveComponent>(foundedActor->GetRootComponent());
        if (rootComponent!=nullptr){
            rootComponent->SetSimulatePhysics(false);
        }
        UE_LOG(LogTemp, Display, TEXT("BuldukDostum"));
        foundedActor->AttachToComponent(this,FAttachmentTransformRules::KeepWorldTransform);
        Mover->setShouldMove(true);
    }
    else 
        Mover->setShouldMove(false);
}

AActor* UTriggerComponent::getAcceptableActor() const{

    TArray<AActor*> actors;

    AActor *foundedActor = nullptr;

    GetOverlappingActors(actors);

    for (int32 i=0;i<actors.Num();i++){

        if (actors[i]->ActorHasTag(acceptableTag)){
            foundedActor = actors[i];
            return foundedActor;
        }     
    }
    return foundedActor;
}

void UTriggerComponent::setMover(UMover *NewMover)
{
    Mover = NewMover;
}
