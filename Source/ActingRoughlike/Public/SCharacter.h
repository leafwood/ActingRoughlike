// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class AProjectileBase;
class UCameraComponent;
class USpringArmComponent;
class USInteractionComponent;
class USAttributeComponent;

UCLASS()
class ACTINGROUGHLIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void SpawnMagicProjectile(TSubclassOf<AProjectileBase> Projectile);

	void MagicAttack();
	void MagicTeleportAttack();
	void MagicBlackHoleAttack();

	UPROPERTY(EditAnywhere,Category = "Attack")
	TSubclassOf<AProjectileBase> MagicProjectile;

	UPROPERTY(EditAnywhere,Category = "Attack")
	TSubclassOf<AProjectileBase> BlackHoleProjectile;

	UPROPERTY(EditAnywhere,Category = "Attack")
	TSubclassOf<AProjectileBase> TeleportProjectile;

	UPROPERTY(EditAnywhere,Category = "Attack")
	UAnimMontage* MagicAttackMontage;

	void Interact();
	
private:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta = (AllowPrivateAccess = "true"))
	USAttributeComponent* AttributeComp;

	FTimerHandle ProjectileTimer;

	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor,USAttributeComponent* OwingComp,float NewHealth,float Delta);

	virtual void PostInitializeComponents() override;

	virtual FVector GetPawnViewLocation() const override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealUp(float Amount = 100.f);

	FORCEINLINE UCameraComponent* GetCamera() const {return Camera;}
};
