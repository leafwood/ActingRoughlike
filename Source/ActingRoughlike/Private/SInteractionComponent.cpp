// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "SGameplayInterface.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FVector EyesLocation;
	FRotator EyesRotation;
	GetOwner()->GetActorEyesViewPoint(EyesLocation,EyesRotation);
	const FVector End = EyesLocation + EyesRotation.Vector() * 1000.f;
	FHitResult OutHit;
	GetWorld()->LineTraceSingleByChannel(OutHit,EyesLocation,End,ECC_Visibility);

	//AActor* HitActor = OutHit.GetActor();

	DrawDebugLine(GetWorld(),EyesLocation,End,FColor::Red,true);
	DrawDebugLine(GetWorld(),EyesLocation,EyesLocation + GetOwner()->GetActorForwardVector() * 1000.f,FColor::Green,true);

	TArray<FHitResult> Hits;
	
	GetWorld()->SweepMultiByChannel(Hits,EyesLocation,End,FQuat::Identity,
							ECC_Visibility,FCollisionShape::MakeSphere(30.f));

	for(FHitResult Hit : Hits)
	{
		AActor* HitActor = Hit.GetActor();
		if(HitActor)
		{
			if(HitActor->Implements<USGameplayInterface>())
			{
				ISGameplayInterface::Execute_Interact(HitActor,Cast<APawn>(GetOwner()));
			}
		}
		DrawDebugSphere(GetWorld(),Hit.Location,30.f,16,FColor::Cyan,false,2.0f);
		break;
	}

	//GetWorld()->SweepMultiByChannel(Hits,)
	
	
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

