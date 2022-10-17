// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHoleProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ABlackHoleProjectile::ABlackHoleProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->SetupAttachment(RootComponent);

	ProjectileMovementComp->InitialSpeed = 800.f;
}

// Called when the game starts or when spawned
void ABlackHoleProjectile::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ABlackHoleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
