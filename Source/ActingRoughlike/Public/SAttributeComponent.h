// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged,
	AActor*,InstigatorActor,
	USAttributeComponent*,OwingComp,
	float,NewHealth,
	float,Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTINGROUGHLIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

protected:

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Attribute")
	float Health;


public:

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	UFUNCTION(BlueprintCallable,Category = "AttributeChange")
	bool ApplyHealthChange(float DeltaDamage);

	UFUNCTION(BlueprintCallable,Category = "AttributeChange")
	bool HealHealth(float DeltaHeal);

	UFUNCTION(BlueprintPure)
	bool GetIsAlive();

	UFUNCTION(BlueprintPure)
	bool GetIsDying();

private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Heaalth",meta = (AllowPrivateAccess = true))
	float MaxHealth;
		
};
