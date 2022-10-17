// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "BlackHoleProjectile.generated.h"

class URadialForceComponent;

/**
 * 
 */
UCLASS()
class ACTINGROUGHLIKE_API ABlackHoleProjectile : public AProjectileBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABlackHoleProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Force")
	URadialForceComponent* RadialForce;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
