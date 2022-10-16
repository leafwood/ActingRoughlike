// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoinChest.h"

#include "Particles/ParticleSystemComponent.h"

void ASCoinChest::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);

	if(LidMesh)
	{
		LidMesh->SetRelativeRotation(FRotator(110.f,0,0));
	}
}

// Sets default values
ASCoinChest::ASCoinChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ChestMesh = CreateDefaultSubobject<UStaticMeshComponent>("ChestMesh");
	RootComponent = ChestMesh;
	
	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(ChestMesh);

	GoldPile = CreateDefaultSubobject<UStaticMeshComponent>("GoldPile");
	GoldPile->SetupAttachment(ChestMesh);
	GoldPile->SetRelativeLocation(FVector(0.f,0.f,30.f));

	Gold_Burst = CreateDefaultSubobject<UParticleSystemComponent>("Gold_Burst");
	Gold_Burst->SetupAttachment(ChestMesh);
	Gold_Burst->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void ASCoinChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASCoinChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

