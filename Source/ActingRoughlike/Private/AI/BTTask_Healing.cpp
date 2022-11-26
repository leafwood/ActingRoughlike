// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Healing.h"
#include "AIController.h"
#include "SAttributeComponent.h"

EBTNodeResult::Type UBTTask_Healing::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto AIController = OwnerComp.GetAIOwner();
	if(ensure(AIController))
	{
		const auto AIPawn = AIController->GetPawn();
		if(ensure(AIPawn))
		{
			const auto AttributeComp = Cast<USAttributeComponent>(AIPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
			if(ensure(AttributeComp))
			{
				AttributeComp->HealHealth(100.f);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
