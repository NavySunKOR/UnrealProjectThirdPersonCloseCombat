// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CustomMoveTo.h"
#include <AIModule/Classes/AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "CombatCharacterBase.h"


EBTNodeResult::Type UBTTask_CustomMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (character == nullptr)
		character = Cast<ACombatCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	character->MoveVertical(character->GetVelocity().Size());

	return EBTNodeResult::Succeeded;
}

void UBTTask_CustomMoveTo::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (character == nullptr)
		character = Cast<ACombatCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());

	UE_LOG(LogTemp, Warning, TEXT("Velocity : %f"), character->GetVelocity().Size());

	character->MoveVertical(character->GetVelocity().Size());
}
