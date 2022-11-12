// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SAIController.generated.h"



/**
 * 
 */
UCLASS()
class ACTINGROUGHLIKE_API ASAIController : public AAIController
{
	GENERATED_BODY()
	
	ASAIController();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "AI")
	UBehaviorTree* AiBehaviorTree;

	
};
