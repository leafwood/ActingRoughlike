// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "TeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTINGROUGHLIKE_API ATeleportProjectile : public AProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Explode_Implementation() override;
	
	UFUNCTION()
	void TeleportInstigator();

private:
	FTimerHandle TeleportTimer;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
