// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction.h"

void USAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp,Log,TEXT("Running on %s"),*GetNameSafe(this));
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp,Log,TEXT("Stopping on %s"),*GetNameSafe(this));
}

UWorld* USAction::GetWorld() const
{
	//Outer is set when creating action via NewObject()
	UActorComponent* Comp =  Cast<UActorComponent>(GetOuter());
    if(Comp)
    {
        return Comp->GetWorld();
    }
	return nullptr;
}
