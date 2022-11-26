// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

#include "SGameModeBase.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
: MaxHealth(100.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}


USAttributeComponent* USAttributeComponent::GetAttributeComp(AActor* FromActor)
{
	if(FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(StaticClass()));
	}
	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* FromActor)
{
	auto AttributeComp = GetAttributeComp(FromActor);
	if(AttributeComp){return AttributeComp->GetIsAlive();}
	return false;
}


bool USAttributeComponent::ApplyHealthChange(AActor* DamageInstigator,float DeltaDamage)
{
	if(Health == 0.f){return false;}
	if(!GetOwner()->CanBeDamaged()) {return false;}
	
	const float DamageAmount = FMath::Clamp(DeltaDamage,0.f,Health);
	Health -= DamageAmount;

	if(DamageAmount > 0.f && !GetIsAlive())
	{
		auto GameMode = GetWorld()->GetAuthGameMode<ASGameModeBase>();
		if(GameMode) [[likely]]
		{
			GameMode->OnActorKilled(GetOwner(),DamageInstigator);
		}
	}
	

	OnHealthChanged.Broadcast(DamageInstigator,this,Health,-DamageAmount);
	
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

bool USAttributeComponent::GetIsDying()
{
	if(!GetIsAlive()) {return false;}
	return Health <= 30.f;
}

bool USAttributeComponent::Kill(AActor* Instigator)
{
	return ApplyHealthChange(Instigator,MaxHealth);
}
