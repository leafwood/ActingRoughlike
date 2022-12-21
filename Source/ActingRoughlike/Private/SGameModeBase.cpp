// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"

#include "EngineUtils.h"
#include "SAttributeComponent.h"
#include "SCharacter.h"
#include "EnvironmentQuery/EnvQuery.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

static TAutoConsoleVariable<bool> CVarDoSpawnBots(TEXT("FV.DoSpawnBots"),true,TEXT("Whether allowed to spanw bots"),ECVF_Cheat);

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
	if(!CVarDoSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp,Warning,TEXT("Spawn Bots disabled,stop spawning bots."));
		return;
	}
	
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
		TArray<FVector> Locations =  QueryInstance->GetResultsAsLocations();
		if(Locations.Num()>0)
		{
			GetWorld()->SpawnActor<AActor>(AI_BP,Locations[0],FRotator::ZeroRotator);
		}
	}
}


void ASGameModeBase::KillAll()
{
	for(TActorIterator<ASAICharacter> Iter{GetWorld()};Iter;++Iter)
	{
		USAttributeComponent::GetAttributeComp(*Iter)->Kill(this);
	}
}

void ASGameModeBase::OnActorKilled(AActor* Victim, AActor* Killer)
{
	auto Player = Cast<ASCharacter>(Victim);
	if(Player) [[unlikely]]
	{
		FTimerHandle RespawnPlayerTimer;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this,"RespawnPlayerElapsed",Player->GetController());
		float RespawnDelay {10.f};
		GetWorldTimerManager().SetTimer(RespawnPlayerTimer,TimerDelegate,RespawnDelay,false);
	}
	
	UE_LOG(LogTemp,Warning,TEXT("Onactorkilled called,some actor died"));
}


void ASGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if(ensure(Controller))
	{
		Controller->UnPossess();
		RestartPlayer(Controller);
	}
}