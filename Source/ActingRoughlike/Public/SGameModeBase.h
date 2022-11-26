// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

class UEnvQueryInstanceBlueprintWrapper;
class UEnvQuery;
class ASAICharacter;

/**
 * 
 */
UCLASS()
class ACTINGROUGHLIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	ASGameModeBase();
	
	virtual void StartPlay() override;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float QueryDelay;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UEnvQuery* GetSpawnLocationQuery;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Difficulty")
	UCurveFloat* SpawnDifficultyCurve;
	
	FTimerHandle QueryTimeHandle;

	UFUNCTION()
	void QueryTimerElapsed();

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UPROPERTY(EditAnywhere,Category="AI")
	TSubclassOf<ASAICharacter> AI_BP;

	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);


public:
	UFUNCTION(Exec)
	void KillAll();

	virtual void OnActorKilled(AActor* Victim,AActor* Killer);
};
