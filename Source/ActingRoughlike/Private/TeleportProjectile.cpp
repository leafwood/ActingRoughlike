// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ATeleportProjectile::ATeleportProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComp->InitialSpeed = 3500.f;
}

// Called when the game starts or when spawned
void ATeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TeleportTimer,this,&ATeleportProjectile::Explode,0.25f);
}

void ATeleportProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TeleportTimer);
	
	if(ensure(ExplodeParticle))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this,ExplodeParticle,GetActorLocation(),GetActorRotation());
	}
	
	GetWorldTimerManager().SetTimer(TeleportTimer,this,&ATeleportProjectile::TeleportInstigator,0.2f);
}


void ATeleportProjectile::TeleportInstigator()
{
	if(ensure(GetInstigator()))
	{
		GetInstigator()->K2_TeleportTo(GetActorLocation(),FRotator(0.f,GetActorRotation().Yaw,0.f));
	}
	Destroy();
}

// Called every frame
void ATeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}





