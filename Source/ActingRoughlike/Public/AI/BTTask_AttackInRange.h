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
public:
	UBTTask_AttackInRange();
protected:
	UPROPERTY(EditAnywhere,Category = "AITree")
	FBlackboardKeySelector TarActor;

	UPROPERTY(EditAnywhere,Category = "Attack")
	TSubclassOf<AProjectileBase> MagicProjectile;

private:
	UPROPERTY(EditAnywhere,Category = "AI")
	float MaxBulletPitchSpread;

	UPROPERTY(EditAnywhere,Category = "AI")
	float MaxBulletYawSpread;
};
