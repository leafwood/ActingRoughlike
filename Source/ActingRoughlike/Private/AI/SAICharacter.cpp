// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "SAttributeComponent.h"
#include "SWorldUserWidget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ASAICharacter::ASAICharacter():
ParamName("TimeToHit")
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned; 

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	SensingComp = CreateDefaultSubobject<UPawnSensingComponent>("SensingComp");

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void ASAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASAICharacter::Set_BB_PlayerActor(APawn* Player)
{
	const auto AIController = Cast<AAIController>(GetController());
	if(AIController)
	{
		const auto BlackboardComp = AIController->GetBlackboardComponent();
		if(ensureMsgf(BlackboardComp,TEXT("AIController BlackBoardComp is Minssing,Please check in the BehaviorTreeComp of the controller")))
		{
			BlackboardComp->SetValueAsObject("PlayerActor",Player);
		}
	}
}

void ASAICharacter::OnSeePawn(APawn* Player)
{
	Set_BB_PlayerActor(Player);
}


// Called every frame
void ASAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SensingComp->OnSeePawn.AddDynamic(this,&ASAICharacter::OnSeePawn);
	AttributeComp->OnHealthChanged.AddDynamic(this,&ASAICharacter::OnHealthChanged);
	
}

void ASAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwingComp, float NewHealth,
	float Delta)
{
	if(InstigatorActor == this) {return;}
	
	if(Delta < 0.f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(ParamName,GetWorld()->TimeSeconds);

		if(!ActiveHealthBar)
		{
			ActiveHealthBar = CreateWidget<USWorldUserWidget>(GetWorld(),HealthBarWidget);
			if(ActiveHealthBar)
			{
				ActiveHealthBar->SetActorToAttach(this);
				ActiveHealthBar->AddToViewport();
			}
		}
		
		if(!AttributeComp->GetIsAlive())
		{
			auto AIController = Cast<AAIController>(GetController());
			if(AIController)
			{
				AIController->GetBrainComponent()->StopLogic("Killed");
			}

			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");
			
			SetLifeSpan(10.f);

			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();
		}
		Set_BB_PlayerActor(Cast<APawn>(InstigatorActor));
	}
}

