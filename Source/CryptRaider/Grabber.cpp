// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
    UPhysicsHandleComponent *PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr){
		
		UE_LOG(LogTemp,Display,TEXT("YOK DOSTUM"));
		return PhysicsHandle;
	}
	else {
		return PhysicsHandle;
	}
}

bool UGrabber::getHit(FHitResult& outHit)
{

    UWorld *World = GetWorld();

	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	FVector startPosition = GetComponentLocation();
	FVector endPosition = startPosition + GetForwardVector() * maxGrabDistance;
	//DrawDebugLine(World,startPosition,endPosition,FColor::Red);
	//DrawDebugSphere(World,endPosition,10,10,FColor::Cyan,true,5);
	FCollisionShape sphere = FCollisionShape::MakeSphere(grabRadius);
	bool isHit;
	isHit = World->SweepSingleByChannel(outHit,startPosition,endPosition,FQuat::Identity,ECC_GameTraceChannel2,sphere);

	return isHit;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	maxGrabDistance = 400;
	if (UPhysicsHandleComponent *PhsicsHandle = GetPhysicsHandle()){

		UE_LOG(LogTemp,Display,TEXT("VAR DOSTUM"));
	}
	else {
		UE_LOG(LogTemp,Display,TEXT("YOK DOSTUM"));
	}	
}
	

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr){
		
		UE_LOG(LogTemp,Display,TEXT("YOK DOSTUM"));
		return;
		
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr){
		FVector targetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;
		
		PhysicsHandle->SetTargetLocationAndRotation(targetLocation,GetComponentRotation());
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp,Display,TEXT("Released"));
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr){
		
		UE_LOG(LogTemp,Display,TEXT("YOK DOSTUM"));
		return;
		
	}
	AActor* GrabbedComponent = nullptr;
	if (PhysicsHandle->GetGrabbedComponent()!=nullptr)
		GrabbedComponent = PhysicsHandle->GetGrabbedComponent()->GetOwner();
	if (GrabbedComponent == nullptr){

		return;
	}
	if (GrabbedComponent->ActorHasTag("Holding"))
		GrabbedComponent->Tags.Remove("Holding");
	PhysicsHandle->ReleaseComponent();

}

void UGrabber::Grab()
{
	FHitResult outHit;
	bool isHit = getHit(outHit);
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr){
		
		UE_LOG(LogTemp,Display,TEXT("YOK DOSTUM"));
		return;
		
	}	
	if (isHit){
		UE_LOG(LogTemp,Display,TEXT("You have Hitted : %s"),*outHit.GetActor()->GetActorNameOrLabel());
		UPrimitiveComponent *hitBody = outHit.GetComponent();
		if (!outHit.GetActor()->ActorHasTag("Holding"))
			outHit.GetActor()->Tags.Add("Holding");
		hitBody->WakeAllRigidBodies();
		AActor *HitActor = outHit.GetActor();
		PhysicsHandle->GrabComponentAtLocationWithRotation(hitBody,NAME_None,outHit.ImpactPoint,GetComponentRotation());
		//PhysicsHandle->SetTargetLocationAndRotation(targetLocation,GetComponentRotation());
	}
}
