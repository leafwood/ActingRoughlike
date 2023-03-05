// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "DrawDebugHelpers.h"
#include "ProjectileBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SInteractionComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SAttributeComponent.h"
#include "SActionComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraBoom);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	ActionComp = CreateDefaultSubobject<USActionComponent>("ActionComp");

	this->bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this,&ASCharacter::OnHealthChanged);
}

FVector ASCharacter::GetPawnViewLocation() const
{
	return GetCamera()->GetComponentLocation();
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	for(auto ActionClass : DefaultActions)
	{
		ActionComp->AddAction(ActionClass);
	}
}

float ASCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	//AttributeComp->ApplyHealthChange(nullptr,Damage);
	
	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwingComp, float NewHealth,
	float Delta)
{
	if(!(NewHealth>0.f))
	{
		APlayerController* PController = Cast<APlayerController>(GetController());
		DisableInput(PController);
	}
	GetMesh()->SetScalarParameterValueOnMaterials(FName("TimeToHit"),GetWorld()->TimeSeconds);
}


// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump",EInputEvent::IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("MagicAttack",EInputEvent::IE_Pressed,this,&ASCharacter::MagicAttack);
	PlayerInputComponent->BindAction("TeleportAttack",EInputEvent::IE_Pressed,this,&ASCharacter::MagicTeleportAttack);
	PlayerInputComponent->BindAction("BlackHoleAttack",EInputEvent::IE_Pressed,this,&ASCharacter::MagicBlackHoleAttack);
	
	PlayerInputComponent->BindAction("Interact",EInputEvent::IE_Pressed,this,&ASCharacter::Interact);

	PlayerInputComponent->BindAction("Sprint",EInputEvent::IE_Pressed,this,&ASCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint",EInputEvent::IE_Released,this,&ASCharacter::SprintStop);

	PlayerInputComponent->BindAxis("MoveForward",this,&ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("lookup",this,&APawn::AddControllerPitchInput);

}

void ASCharacter::HealUp(float Amount)
{
	AttributeComp->HealHealth(Amount);
}

void ASCharacter::MoveForward(float Value)
{
	const FRotator ControllerRotator = FRotator(0.f,GetController()->GetControlRotation().Yaw,0.f);

	AddMovementInput(ControllerRotator.Vector() * Value);
}

void ASCharacter::MoveRight(float Value)
{
	const FRotator ControllerRotator = FRotator(0.f,GetController()->GetControlRotation().Yaw,0.f);
	const FVector MoveDirection = UKismetMathLibrary::GetRightVector(ControllerRotator);
	AddMovementInput(MoveDirection * Value);
}

void ASCharacter::MagicAttack()
{
	// UAnimInstance* AnimIns = GetMesh()->GetAnimInstance();
	// if(AnimIns && MagicAttackMontage)
	// {
	// 	AnimIns->Montage_Play(MagicAttackMontage);
	// 	SpawnMagicProjectile(MagicProjectile);
	// }
	
	ActionComp->StartActionByName(this,"PrimaryAttack");
}

void ASCharacter::MagicTeleportAttack()
{
	// UAnimInstance* AnimIns = GetMesh()->GetAnimInstance();
	// if(AnimIns && TeleportProjectile)
	// {
	// 	AnimIns->Montage_Play(MagicAttackMontage);
	// 	SpawnMagicProjectile(TeleportProjectile);
	// }
	ActionComp->StartActionByName(this,"Dash");
}

void ASCharacter::MagicBlackHoleAttack()
{
	// UAnimInstance* AnimIns = GetMesh()->GetAnimInstance();
	// if(AnimIns && BlackHoleProjectile)
	// {
	// 	AnimIns->Montage_Play(MagicAttackMontage);
	// 	SpawnMagicProjectile(BlackHoleProjectile);
	// }
	ActionComp->StartActionByName(this,"BlackHole");
}

void ASCharacter::SprintStart()
{
	ActionComp->StartActionByName(this,"Sprint");
}

void ASCharacter::SprintStop()
{
	ActionComp->StopActionByName(this,"Sprint");
}

void ASCharacter::Interact()
{
	if(InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}
