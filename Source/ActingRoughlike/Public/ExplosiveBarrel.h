// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "ExplosiveBarrel.generated.h"

UCLASS()
class ACTINGROUGHLIKE_API AExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosiveBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverLap(
   UPrimitiveComponent* OverlappedComponent,
   AActor* OtherActor,
   UPrimitiveComponent* OtherComp,
   int32 OtherBodyIndex,
   bool bFromSweep,
   const FHitResult& SweepResult);

	
private:
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BarrelMesh;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	URadialForceComponent* RadialForce;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void Explode();
};
