// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

#include "GameFramework/Character.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
: Health(100.f),
MaxHealth(100.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool USAttributeComponent::ApplyHealthChange(float DeltaDamage)
{
	if(Health == 0.f){return false;}
	
	const float DamageAmount = FMath::Clamp(DeltaDamage,0.f,Health);
	Health -= DamageAmount;

	OnHealthChanged.Broadcast(nullptr,this,Health,-DamageAmount);
	
	return true;
}

bool USAttributeComponent::HealHealth(float DeltaHeal)
{
	if(Health == MaxHealth){return false;}

	const float HealAmount = FMath::Clamp(DeltaHeal,0.f,MaxHealth-Health);
	Health += HealAmount;
	
	OnHealthChanged.Broadcast(nullptr,this,Health,HealAmount);
	return true;
}

bool USAttributeComponent::GetIsAlive()
{
	return Health > 0.f;
}
