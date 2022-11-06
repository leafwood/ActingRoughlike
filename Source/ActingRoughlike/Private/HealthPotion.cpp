// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPotion.h"

#include "SAttributeComponent.h"

bool AHealthPotion::ApplyBuffs(APawn* InstigatorPawn)
{
	Super::ApplyBuffs(InstigatorPawn);

	USAttributeComponent* AttributeComp = InstigatorPawn->FindComponentByClass<USAttributeComponent>();

	return AttributeComp->HealHealth(HealthAmount);
}
