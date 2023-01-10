// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged,
	AActor*,InstigatorActor,
	int32,NewCredits,
	int32,Delta);

/**
 * 
 */
UCLASS()
class ACTINGROUGHLIKE_API ASPlayerState : public APlayerState
{
public:
	int32 GetCredits() const {return Credits;}

	void SetCredits(int32 NewCredits){this->Credits = NewCredits;}

private:
	GENERATED_BODY()

public:
	ASPlayerState();

	UPROPERTY(BlueprintAssignable)
	FOnCreditsChanged OnCreditsChanged;

	UFUNCTION(BlueprintCallable)
	void RewardCredits(AActor* CreditsInstigator,int32 RewardAmount);

	UFUNCTION(BlueprintCallable)
	void ConsumeCredits(AActor* CreditsInstigator,int32 ConsumeAmount);
protected:
	
	UPROPERTY(Replicated,BlueprintReadOnly)
	int32 PlayerArmour;
	void OnRep_PlayerArmour()
	{
	}

	UPROPERTY(Replicated,BlueprintReadOnly)
	int32 Credits;
	void OnRep_Credits()
	{
	}
	
};
