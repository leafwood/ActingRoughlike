// Fill out your copyright notice in the Description page of Project Settings.


#include "Lever.h"

#include "ExplosiveBarrel.h"

// Sets default values
ALever::ALever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LeverMesh = CreateDefaultSubobject<UStaticMeshComponent>("LeverMesh");
	LeverMesh->SetupAttachment(RootComponent);
	LeverMesh->SetRelativeRotation(FRotator(30.f,0.f,0.f));

}

// Called when the game starts or when spawned
void ALever::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALever::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);

	if(SelectedActor)
	{
		if(SelectedActor->Implements<USGameplayInterface>())
		{
			//ISGameplayInterface::Execute_Interact(SelectedActor,Cast<APawn>(this));
			Execute_Interact(SelectedActor,Cast<APawn>(this));
		}
		else if(Cast<AExplosiveBarrel>(SelectedActor))
		{
			AExplosiveBarrel* Barrel = Cast<AExplosiveBarrel>(SelectedActor);
			Barrel->Explode();
		}
	}

	LeverMesh->SetRelativeRotation(FRotator(-30.f,0.f,0.f));
	
}

// Called every frame
void ALever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



