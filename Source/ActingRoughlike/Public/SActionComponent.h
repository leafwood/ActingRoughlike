// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SActionComponent.generated.h"


class USAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTINGROUGHLIKE_API USActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USActionComponent();

	UFUNCTION(BlueprintCallable,Category="Action")
	void AddAction(TSubclassOf<USAction> ActionClass);

	UFUNCTION(BlueprintCallable,Category="Action")
	bool StartActionByName(AActor* Instigator,FName ActionName);
	UFUNCTION(BlueprintCallable,Category="Action")
	bool StopActionByName(AActor* Instigator,FName ActionName);

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<USAction*> Actions;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
