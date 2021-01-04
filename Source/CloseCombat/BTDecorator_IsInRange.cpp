// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInRange.h"
#include <Kismet/GameplayStatics.h>
#include <BehaviorTree/BehaviorTree.h>
#include <AIController.h>

bool UBTDecorator_IsInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	APawn* playerPawn;
	AAIController* aiController;
	playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	aiController = OwnerComp.GetAIOwner();
	float distances = (playerPawn->GetActorLocation() - aiController->GetPawn()->GetActorLocation()).Size();
	UE_LOG(LogTemp, Warning, TEXT("Range : %f"), distances);
	if (distances < 150.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("IsInRange"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("IsNotInRange"));
		return false;
	}
}