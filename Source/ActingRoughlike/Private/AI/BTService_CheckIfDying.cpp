// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_CheckIfDying.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_CheckIfDying::UBTService_CheckIfDying()
{
	Interval = 1.f;
}

void UBTService_CheckIfDying::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if(BlackBoard)
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
					const auto IsDying = AttributeComp->GetIsDying();
					BlackBoard->SetValueAsBool(IsDyingKey.SelectedKeyName,IsDying);
				}
			}
		}
	}
}
