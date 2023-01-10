// Fill out your copyright notice in the Description page of Project Settings.


#include "CreditsCoin.h"

#include "SPlayerState.h"

ACreditsCoin::ACreditsCoin()
{
}

bool ACreditsCoin::ApplyBuffs(APawn* InstigatorPawn)
{
	if(InstigatorPawn->GetController()->PlayerState)
	{
		InstigatorPawn->GetController()->GetPlayerState<ASPlayerState>()->RewardCredits(InstigatorPawn,30);
		return true;
	}
	return false;
}
