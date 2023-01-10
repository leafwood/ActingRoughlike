// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotion.h"

#include "SAttributeComponent.h"
#include "SPlayerState.h"

bool AHealthPotion::ApplyBuffs(APawn* InstigatorPawn)
{
	Super::ApplyBuffs(InstigatorPawn);

	if(InstigatorPawn->GetController()->PlayerState)
	{
		auto SPlayerState = InstigatorPawn->GetController()->GetPlayerState<ASPlayerState>();
		if(SPlayerState->GetCredits() >= 50)
		{
			SPlayerState->ConsumeCredits(InstigatorPawn,50);
			USAttributeComponent* AttributeComp = InstigatorPawn->FindComponentByClass<USAttributeComponent>();
			return AttributeComp->HealHealth(HealthAmount);
		}
	}
	return false;
}
