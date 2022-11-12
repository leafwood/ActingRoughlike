// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"

#include "EngineUtils.h"
#include "SAttributeComponent.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

ASGameModeBase::ASGameModeBase() :
QueryDelay(2.f)
{
	
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(QueryTimeHandle,this,&ASGameModeBase::QueryTimerElapsed,QueryDelay,true);
	
}

void ASGameModeBase::QueryTimerElapsed()
{
	const auto QueryInstance = UEnvQueryManager::RunEQSQuery(
		this,GetSpawnLocationQuery,this,EEnvQueryRunMode::RandomBest5Pct,nullptr);

	if(ensureMsgf(QueryInstance,TEXT("StartPlay Query Running Failed")))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this,&ASGameModeBase::OnQueryCompleted);
	}
}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus == EEnvQueryStatus::Success)
	{

		int32 NrofAliveBots {0};
		for(TActorIterator<ASAICharacter> Iter{GetWorld()};Iter;++Iter)
		{
			ASAICharacter* Bot = *Iter;

			const auto AttributeComp = Cast<USAttributeComponent>(Bot->GetComponentByClass(USAttributeComponent::StaticClass()));
			if(ensure(AttributeComp))
			{
				if(AttributeComp->GetIsAlive())
				{
					NrofAliveBots++;
				}
			}
		}

		float SpawnMaxLimit {10.f};
		
		if(SpawnDifficultyCurve)
		{
			SpawnMaxLimit = SpawnDifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
		}
		
		if(NrofAliveBots >= SpawnMaxLimit){return;}
		
		
		TArray<FVector> Locations =  QueryInstance->GetResultsAsLocations();
		if(Locations.Num()>0)
		{
			GetWorld()->SpawnActor<AActor>(AI_BP,Locations[0],FRotator::ZeroRotator);
		}
	}
}

