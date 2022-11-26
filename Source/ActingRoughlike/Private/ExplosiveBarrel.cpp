// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"

#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>("BarrelMesh");
	SetRootComponent(BarrelMesh);

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->SetupAttachment(RootComponent);

	RadialForce->SetAutoActivate(false);
	RadialForce->AddCollisionChannelToAffect(ECC_WorldDynamic);
	RadialForce->Radius = 1000.f;

	ForceRange = CreateDefaultSubobject<USphereComponent>("ForceRange");
	ForceRange->SetupAttachment(RootComponent);;
	ForceRange->SetSphereRadius(1000.f);

}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

	BarrelMesh->OnComponentBeginOverlap.AddDynamic(this,&AExplosiveBarrel::OnSphereOverLap);
	
}

// Called every frame
void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExplosiveBarrel::Explode()
{
	
	RadialForce->FireImpulse();

	TArray<AActor*> Targets;
	ForceRange->GetOverlappingActors(Targets);
	for(auto& target : Targets)
	{
		USAttributeComponent* AttributeComp = target->FindComponentByClass<USAttributeComponent>();
		if(AttributeComp)
		{
			AttributeComp->ApplyHealthChange(this,50);
		}
	}
}

void AExplosiveBarrel::OnSphereOverLap(UPrimitiveComponent* OverlappedComponent,
                                       AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp,
                                       int32 OtherBodyIndex,
                                       bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	Explode();
	BarrelMesh->SetScalarParameterValueOnMaterials("TimeToHit",GetWorld()->TimeSeconds);
	UE_LOG(LogTemp,Warning,TEXT("OtherActor : %s"),*GetNameSafe(OtherActor));

	FString CombinedString = FString::Printf(TEXT("Hit At Location By: %s"),*GetNameSafe(OtherActor));
	DrawDebugString(GetWorld(),OtherActor->GetActorLocation(),CombinedString,nullptr,FColor::Cyan,2.0f,true);

}



