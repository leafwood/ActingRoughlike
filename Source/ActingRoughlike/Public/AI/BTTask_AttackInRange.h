// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AttackInRange.generated.h"

class AProjectileBase;

/**
 * 
 */
UCLASS()
class ACTINGROUGHLIKE_API UBTTask_AttackInRange : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere,Category = "AITree")
	FBlackboardKeySelector TarActor;

	UPROPERTY(EditAnywhere,Category = "Attack")
	TSubclassOf<AProjectileBase> MagicProjectile;
};
