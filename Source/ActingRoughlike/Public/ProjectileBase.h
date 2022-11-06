// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class USoundCue;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class ACTINGROUGHLIKE_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Explode();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Explode")
	TSubclassOf<UCameraShakeBase> SpellBurstShake;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Explode")
	UParticleSystem* SpellBurstParticle;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "ExplodeAudio")
	UAudioComponent* ProjectileLoop;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "ExplodeAudio")
	USoundCue* ProjectileBurst;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Explode")
	UParticleSystem* ExplodeParticle;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ParticleComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovementComp;
	
	UFUNCTION()
	void StartingOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Damage")
	float DamageAmount;

private:
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
