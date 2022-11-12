// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "SAttributeComponent.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

// Sets default values
AProjectileBase::AProjectileBase():
DamageAmount(0.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SphereComp = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(SphereComp);
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&AProjectileBase::StartingOverlap);
	SphereComp->OnComponentHit.AddDynamic(this,&AProjectileBase::OnCompHit);

	ParticleComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleFX");
	ParticleComp->SetupAttachment(RootComponent);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovementComp->InitialSpeed = 1000.f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComp->ProjectileGravityScale = 0.f;

	ProjectileLoop = CreateDefaultSubobject<UAudioComponent>("ProjectileLoop");
	ProjectileLoop->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->IgnoreActorWhenMoving(GetInstigator(),true);
	
	if(SpellBurstParticle)
	{
		UGameplayStatics::SpawnEmitterAttached(SpellBurstParticle,GetRootComponent());
	}

	if(SpellBurstShake)
	{
		UGameplayStatics::PlayWorldCameraShake(this,SpellBurstShake,GetActorLocation(),50.f,300.f);
	}
}

void AProjectileBase::Explode_Implementation()
{
	if(!IsPendingKill())
	{
		if(ExplodeParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this,ExplodeParticle,GetActorLocation(),GetActorRotation());
		}

		if(ProjectileBurst)
		{
			UGameplayStatics::PlaySoundAtLocation(this,ProjectileBurst,GetActorLocation(),GetActorRotation());
		}
		
		Destroy();
	}

	if(SpellBurstShake)
	{
		UGameplayStatics::PlayWorldCameraShake(this,SpellBurstShake,GetActorLocation(),50.f,300.f);
	}
}


void AProjectileBase::StartingOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == GetInstigator()) return;
	
	USAttributeComponent* Attributecomp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	if(Attributecomp)
	{
		Attributecomp->ApplyHealthChange(DamageAmount);
	}

	Explode();
}

void AProjectileBase::OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor == GetInstigator()) return;

	Explode();
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

