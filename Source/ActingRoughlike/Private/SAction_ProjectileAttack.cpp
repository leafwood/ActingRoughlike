// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_ProjectileAttack.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

USAction_ProjectileAttack::USAction_ProjectileAttack()
{
	HandSocketName = "Muzzle_01";
	AttackAnimDelay = 0.2f;
}

void USAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	
	ACharacter* PlayerCharacter = Cast<ACharacter>(Instigator);
	
	if(PlayerCharacter)
	{
		PlayerCharacter->GetMesh()->GetAnimInstance()->Montage_Play(AttackAnim);
		UGameplayStatics::SpawnEmitterAttached(CastingEffect,PlayerCharacter->GetMesh(),HandSocketName,FVector::ZeroVector,FRotator::ZeroRotator,EAttachLocation::SnapToTarget);
	
		FTimerHandle TimerHandle_attackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this,"AttackDelay_Elapsed",PlayerCharacter);
	
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_attackDelay,Delegate,AttackAnimDelay,false);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("PlayerNULL"))
	}
}

void USAction_ProjectileAttack::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
}

void USAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);
	FRotator HandRotation = InstigatorCharacter->GetActorRotation();
	
	FHitResult CameraHit;

	FVector CameraStart = InstigatorCharacter->GetPawnViewLocation();
	FVector CameraEnd = InstigatorCharacter->GetPawnViewLocation() + InstigatorCharacter->GetControlRotation().Vector() * 10000.f;
	
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(InstigatorCharacter);
	
	GetWorld()->LineTraceSingleByChannel(CameraHit,CameraStart,CameraEnd,ECC_Visibility,CollisionQueryParams);
	DrawDebugLine(GetWorld(),CameraStart,CameraEnd,FColor::Green,false,2.0f);

	if(CameraHit.bBlockingHit)
	{
		HandRotation =  UKismetMathLibrary::FindLookAtRotation(HandLocation,CameraHit.Location);
	}
	else
	{
		HandRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation,CameraEnd);
	}
	
	const FTransform SpawnTrans = FTransform(HandRotation,HandLocation);
	
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.Instigator = InstigatorCharacter;
	
	if(ProjectileClass && GetWorld())
	{
		GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTrans,SpawnParam);
	}

	StopAction(InstigatorCharacter);
}
