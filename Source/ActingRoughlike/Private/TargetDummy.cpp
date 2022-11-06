// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetDummy.h"


#include "SAttributeComponent.h"

// Sets default values
ATargetDummy::ATargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	AttributeComp->OnHealthChanged.AddDynamic(this,&ATargetDummy::OnHealthChanged);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void ATargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ATargetDummy::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwingComp, float NewHealth,
	float Delta)
{
	if(Delta < 0.f) return;
	Mesh->SetScalarParameterValueOnMaterials("TimeToHit",GetWorld()->TimeSeconds);
}

// Called every frame
void ATargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

