// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatAIController.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <Kismet/GameplayStatics.h>

void ACombatAIController::BeginPlay()
{
	Super::BeginPlay();
	blackboard = GetBlackboardComponent();
	playerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	RunBehaviorTree(aiTree);
}

void ACombatAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//blackboard->SetValueAsVector(TEXT("PlayerPosition"), playerActor->GetActorLocation());
}