// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PotionBase.h"
#include "HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class ACTINGROUGHLIKE_API AHealthPotion : public APotionBase
{
	GENERATED_BODY()
public:
	explicit AHealthPotion()
		: HealthAmount(50.f)
	{
	}

protected:
	virtual bool ApplyBuffs(APawn* InstigatorPawn) override;

	

private:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "HealthChange",meta = (AllowPrivateAccess = true))
	float HealthAmount;
	
};
