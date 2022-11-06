// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PotionBase.generated.h"

UCLASS()
class ACTINGROUGHLIKE_API APotionBase : public AActor,public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APotionBase();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Base")
	USphereComponent* PotionCollision;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Base")
	UStaticMeshComponent* PotionMesh;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	virtual bool ApplyBuffs(APawn* InstigatorPawn);

	UFUNCTION()
	void DeactivatePotion();
	
	UFUNCTION()
	void ReactivatePotion();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "PotionCD")
	bool IsAvailable;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "PotionCD")
	float PotionCD;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "PotionCD")
	FTimerHandle PotionReAvailTimer;

};
