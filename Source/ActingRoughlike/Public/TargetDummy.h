// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetDummy.generated.h"

class USAttributeComponent;

UCLASS()
class ACTINGROUGHLIKE_API ATargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor,USAttributeComponent* OwingComp,float NewHealth,float Delta);

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Attribute")
	USAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Attribute")
	UStaticMeshComponent* Mesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
