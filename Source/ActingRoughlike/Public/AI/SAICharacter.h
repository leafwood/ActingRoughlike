// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class USAttributeComponent;
class UPawnSensingComponent;
class USWorldUserWidget;

UCLASS()
class ACTINGROUGHLIKE_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Set_BB_PlayerActor(APawn* Player);

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Attribute")
	USAttributeComponent* AttributeComp;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "AI")
	UPawnSensingComponent* SensingComp;

	UFUNCTION()
	void OnSeePawn(APawn* Player);

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor,
	USAttributeComponent* OwingComp,
	float NewHealth,
	float Delta);
	
	UPROPERTY()
	USWorldUserWidget* ActiveHealthBar;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidget;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere,Category = "Material")
	FName ParamName;

	

};
