// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "CombatCharacterBase.h"
#include "BTTask_CustomMoveTo.generated.h"

/**
 * 
 */
UCLASS()
class CLOSECOMBAT_API UBTTask_CustomMoveTo : public UBTTask_MoveTo
{
	GENERATED_BODY()

private:
	ACombatCharacterBase* character;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
