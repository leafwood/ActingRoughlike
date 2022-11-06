// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionBase.h"

// Sets default values
APotionBase::APotionBase()
	:IsAvailable(true),
PotionCD(10.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PotionCollision = CreateDefaultSubobject<USphereComponent>("PotionCollision");
	RootComponent = PotionCollision;

	PotionMesh = CreateDefaultSubobject<UStaticMeshComponent>("PotionMesh");
	PotionMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APotionBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APotionBase::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);

	if(IsAvailable)
	{
		if(ApplyBuffs(InstigatorPawn))
		{
			DeactivatePotion();
			GetWorldTimerManager().SetTimer(PotionReAvailTimer,this,&APotionBase::ReactivatePotion,PotionCD);
		}
	}
}

bool APotionBase::ApplyBuffs(APawn* InstigatorPawn)
{
	return false;
}

void APotionBase::DeactivatePotion()
{
	IsAvailable = false;
	PotionMesh->SetVisibility(false);
}

void APotionBase::ReactivatePotion()
{
	IsAvailable = true;
	PotionMesh->SetVisibility(true);
}

// Called every frame
void APotionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

