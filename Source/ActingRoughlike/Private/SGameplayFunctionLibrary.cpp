// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayFunctionLibrary.h"

#include "SAttributeComponent.h"

bool USGameModeFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* DamageVictim, float DamageAmount)
{
	auto AttributeComp = USAttributeComponent::GetAttributeComp(DamageVictim);
	if(AttributeComp)
	{
		return AttributeComp->ApplyHealthChange(DamageCauser,DamageAmount);
	}
	return false;
}

bool USGameModeFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* DamageVictim, float DamageAmount,
	const FHitResult& OutHit)
{
	if(ApplyDamage(DamageCauser,DamageVictim,DamageAmount))
	{
		auto PrimitiveComp = OutHit.GetComponent();
		if(PrimitiveComp && PrimitiveComp->IsSimulatingPhysics(OutHit.BoneName))
		{
			PrimitiveComp->AddImpulseAtLocation(-OutHit.ImpactNormal * 30000.f,OutHit.Location,OutHit.BoneName);
			return true;
		}
	}
	return false;
}
