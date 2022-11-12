// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_CheckRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_CheckRange::UBTService_CheckRange()\
:AttackReadyRange(3000.f)
{

	
}

void UBTService_CheckRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if(ensure(BBComp))
	{
		const AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject(TargetActorKey.SelectedKeyName));
		if(TargetActor)
		{
			const AAIController* Controller =  OwnerComp.GetAIOwner();
			const AActor* ThisActor = Controller->GetPawn();
			if(ensure(ThisActor))
			{
				const float Distance = FVector::Distance(TargetActor->GetActorLocation(),ThisActor->GetActorLocation());
				const bool TargetWithinRange = Distance < AttackReadyRange;
				BBComp->SetValueAsBool(WithinRangeKey.SelectedKeyName,TargetWithinRange);
				const bool IsInLineOFSight = Controller->LineOfSightTo(TargetActor);
				BBComp->SetValueAsBool(LineOfSightKey.SelectedKeyName,IsInLineOFSight);
			}
		}
	}
}
