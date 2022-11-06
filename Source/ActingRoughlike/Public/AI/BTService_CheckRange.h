// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckRange.generated.h"

/**
 * 
 */
UCLASS()
class ACTINGROUGHLIKE_API UBTService_CheckRange : public UBTService
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,Category = "AITree")
	FBlackboardKeySelector TargetActorKey;
	
	UPROPERTY(EditAnywhere,Category = "AITree")
	FBlackboardKeySelector WithinRangeKey;
	
	UPROPERTY(EditAnywhere,Category = "AISight")
	FBlackboardKeySelector LineOfSightKey;
	
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
