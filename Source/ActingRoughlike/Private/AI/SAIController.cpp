// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAIController.h"

#include "Kismet/GameplayStatics.h"


ASAIController::ASAIController()
{

	
}

void ASAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(AiBehaviorTree);
	//APawn* Player = UGameplayStatics::GetPlayerPawn(this,0);
	//if(Player)
	//{
	//	UBlackboardComponent* BlackBoard = GetBlackboardComponent();
	//	BlackBoard->SetValueAsVector("PlayerLocation",Player->GetActorLocation());
	//	BlackBoard->SetValueAsObject("PlayerActor",Player);
	//}
}
