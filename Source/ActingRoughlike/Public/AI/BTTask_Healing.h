// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Healing.generated.h"

/**
 * 
 */
UCLASS()
class ACTINGROUGHLIKE_API UBTTask_Healing : public UBTTaskNode
{
	GENERATED_BODY()

	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
