// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SWorldUserWidget.generated.h"

class USizeBox;

/**
 * 
 */
UCLASS()
class ACTINGROUGHLIKE_API USWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;

	float HeightOffSet {150.f};
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadOnly,Category = "AI")
	AActor* ActorToAttach;

public:
	FORCEINLINE AActor* GetActorToAttach() const {return ActorToAttach;}
	FORCEINLINE void SetActorToAttach(AActor* Actor) {ActorToAttach = Actor;}
};
