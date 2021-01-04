// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Attack.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <AIModule/Classes/AIController.h>
#include "CombatCharacterBase.h"

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACombatCharacterBase* character = Cast<ACombatCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr)
		return EBTNodeResult::Failed;
	character->Attack();

	OwnerComp.GetBlackboardComponent()->SetValueAsInt(TEXT("AttackType"), 0);

	return EBTNodeResult::Succeeded;
}