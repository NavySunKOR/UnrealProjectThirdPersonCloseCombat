// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Block.h"
#include <AIModule/Classes/AIController.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "CombatCharacterBase.h"

EBTNodeResult::Type UBTTask_Block::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACombatCharacterBase* character = Cast<ACombatCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr)
		return EBTNodeResult::Failed;
	character->BlockOn();

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, FTimerDelegate::CreateLambda([&]() {
		ACombatCharacterBase* character = Cast<ACombatCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
		if (character != nullptr)
		{
			character->BlockOff();
		}
		})
		, 1.f
		, false);

	OwnerComp.GetBlackboardComponent()->SetValueAsInt(TEXT("AttackType"),0);

	return EBTNodeResult::Succeeded;
}