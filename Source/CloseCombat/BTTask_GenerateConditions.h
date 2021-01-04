// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GenerateConditions.generated.h"

/**
 * 
 */
UCLASS()
class CLOSECOMBAT_API UBTTask_GenerateConditions : public UBTTaskNode
{
	GENERATED_BODY()
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
