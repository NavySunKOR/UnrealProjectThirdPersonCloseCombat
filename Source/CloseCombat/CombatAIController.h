// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CombatAIController.generated.h"

/**
 * 
 */
UCLASS()
class CLOSECOMBAT_API ACombatAIController : public AAIController
{
	GENERATED_BODY()
private:
	virtual void BeginPlay() override;
	UBlackboardComponent* blackboard;
	AActor* playerActor;
	UPROPERTY(EditAnywhere)
	UBehaviorTree* aiTree;
public:
	virtual void Tick(float DeltaTime) override;
};
