// Fill out your copyright notice in the Description page of Project Settings.


#include <BehaviorTree/BlackboardComponent.h>
#include "BTTask_GenerateConditions.h"

EBTNodeResult::Type UBTTask_GenerateConditions::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	int created = rand() % 2;
	if (created == 0)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(TEXT("AttackType"), 1);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(TEXT("AttackType"), 2);
	}

	return EBTNodeResult::Succeeded;
}