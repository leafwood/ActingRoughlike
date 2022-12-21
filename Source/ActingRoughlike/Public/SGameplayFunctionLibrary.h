// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SGameplayFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ACTINGROUGHLIKE_API USGameModeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category = "Gameplay")
	static bool ApplyDamage(AActor* DamageCauser,AActor* DamageVictim,float DamageAmount);

	UFUNCTION(BlueprintCallable,Category = "Gameplay")
	static bool ApplyDirectionalDamage(AActor* DamageCauser,AActor* DamageVictim,float DamageAmount,const FHitResult& OutHit);
	
};
