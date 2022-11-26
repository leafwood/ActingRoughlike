// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckIfDying.generated.h"

/**
 * 
 */
UCLASS()
class ACTINGROUGHLIKE_API UBTService_CheckIfDying : public UBTService
{
	GENERATED_BODY()

	UBTService_CheckIfDying();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnywhere,Category = "Health")
	FBlackboardKeySelector IsDyingKey;
};
