// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_LockOn.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <AIModule/Classes/AIController.h>
#include <Kismet/GameplayStatics.h>
#include "CombatCharacterBase.h"

EBTNodeResult::Type UBTTask_LockOn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	ACombatCharacterBase* character = Cast<ACombatCharacterBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr)
		return EBTNodeResult::Failed;


	if(!character->IsLockOn())
		character->LockOn(true);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPosition"), UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation());

	return EBTNodeResult::Succeeded;
}