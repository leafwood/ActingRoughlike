// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "SMagicProjectile.generated.h"

UCLASS()
class ACTINGROUGHLIKE_API ASMagicProjectile : public AProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
