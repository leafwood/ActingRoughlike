// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SAction_ProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class ACTINGROUGHLIKE_API USAction_ProjectileAttack : public USAction
{
	GENERATED_BODY()

public:
	USAction_ProjectileAttack();

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;
	
protected:
    UPROPERTY(EditAnywhere,Category = "Attack")
    TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(VisibleAnywhere,Category = "Effect")
	FName HandSocketName;

	UPROPERTY(EditDefaultsOnly,Category = "Attack")
	float AttackAnimDelay;

	UPROPERTY(EditAnywhere,Category = "Attack")
	UAnimMontage* AttackAnim;

	UPROPERTY(EditAnywhere,Category = "Attack")
	UParticleSystem* CastingEffect;

	UFUNCTION()
	void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);
};
