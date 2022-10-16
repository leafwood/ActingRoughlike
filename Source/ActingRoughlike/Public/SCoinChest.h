// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SCoinChest.generated.h"

UCLASS()
class ACTINGROUGHLIKE_API ASCoinChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere,Category = "Chest")
	float TargetPitch;
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
	// Sets default values for this actor's properties
	ASCoinChest();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* ChestMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* GoldPile;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UParticleSystemComponent* Gold_Burst;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
