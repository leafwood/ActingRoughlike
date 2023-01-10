// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupBase.h"
#include "CreditsCoin.generated.h"

/**
 * 
 */
UCLASS()
class ACTINGROUGHLIKE_API ACreditsCoin : public APotionBase
{
	GENERATED_BODY()

public:
	ACreditsCoin();

protected:
	virtual bool ApplyBuffs(APawn* InstigatorPawn) override;
};
