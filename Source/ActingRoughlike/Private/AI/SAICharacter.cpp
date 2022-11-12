// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned; 

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");
	SensingComp = CreateDefaultSubobject<UPawnSensingComponent>("SensingComp");

}

// Called when the game starts or when spawned
void ASAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASAICharacter::OnSeePawn(APawn* Player)
{
	auto AIController = Cast<AAIController>(GetController());
	if(AIController)
	{
		auto BlackboardComp = AIController->GetBlackboardComponent();
		if(ensureMsgf(BlackboardComp,TEXT("AiController BlackBoardComp is Minssing,Please check in the BehaviorTreeComp of the controller")))
		{
			BlackboardComp->SetValueAsObject("PlayerActor",Player);
		}
	}
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
	if(!AttributeComp->GetIsAlive())
	{
		Destroy();
	}
}

