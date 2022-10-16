// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SInteractionComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

	this->bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

float ASCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
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
	PlayerInputComponent->BindAction("Attack",EInputEvent::IE_Pressed,this,&ASCharacter::MagicAttack);
	PlayerInputComponent->BindAction("Interact",EInputEvent::IE_Pressed,this,&ASCharacter::Interact);

	PlayerInputComponent->BindAxis("MoveForward",this,&ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup",this,&APawn::AddControllerPitchInput);

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

void ASCharacter::SpawnMagicProjectile()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FRotator HandRotation = GetMesh()->GetSocketRotation("Muzzle_01");
	const FTransform SpawnTrans = FTransform(GetActorRotation(),HandLocation);
	
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.Instigator = this;
	
	if(MagicProjectile && GetWorld())
	{
		GetWorld()->SpawnActor<AActor>(MagicProjectile,SpawnTrans,SpawnParam);
	}
}

void ASCharacter::MagicAttack()
{
	UAnimInstance* AnimIns = GetMesh()->GetAnimInstance();
	if(AnimIns && MagicAttackMontage)
	{
		AnimIns->Montage_Play(MagicAttackMontage);
		SpawnMagicProjectile();
	}

	//SpawnMagicProjectile();
	//GetWorldTimerManager().SetTimer(ProjectileTimer,this,&ASCharacter::SpawnMagicProjectile,0.05f);
}

void ASCharacter::Interact()
{
	if(InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}




