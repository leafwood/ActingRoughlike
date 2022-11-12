// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_AttackInRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "ProjectileBase.h"

EBTNodeResult::Type UBTTask_AttackInRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto AIController =  OwnerComp.GetAIOwner();
	if(ensure(AIController))
	{
		const auto Character = Cast<ACharacter>(AIController->GetPawn());
		if(!Character)
		{
			return EBTNodeResult::Failed;
		}
		const FVector MuzzleLocation = Character->GetMesh()->GetSocketLocation("Muzzle_01");

		auto TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TarActor.SelectedKeyName));
		if(TargetActor)
		{
			auto Direction = (TargetActor->GetActorLocation() - MuzzleLocation).Rotation();
			
			FActorSpawnParameters SpawnParam;
			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParam.Instigator = AIController->GetPawn();
			
			if(MagicProjectile && GetWorld())
			{
				auto ParticleSpawned = GetWorld()->SpawnActor<AActor>(MagicProjectile,MuzzleLocation,Direction,SpawnParam);
				return ParticleSpawned ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
			}
		}
	}
	return EBTNodeResult::Failed;
}
