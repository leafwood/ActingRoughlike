// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

#include "Net/UnrealNetwork.h"

ASPlayerState::ASPlayerState() :
PlayerArmour(0),
Credits(0)
{
	SetReplicates(true);
}

void ASPlayerState::RewardCredits(AActor* CreditsInstigator,int32 RewardAmount)
{
	Credits += RewardAmount;
	OnCreditsChanged.Broadcast(CreditsInstigator,Credits,RewardAmount);
}

void ASPlayerState::ConsumeCredits(AActor* CreditsInstigator,int32 ConsumeAmount)
{
	Credits -= ConsumeAmount;
	OnCreditsChanged.Broadcast(CreditsInstigator,Credits,-ConsumeAmount);
}

void ASPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASPlayerState, PlayerArmour);
	DOREPLIFETIME(ASPlayerState, Credits);
}
