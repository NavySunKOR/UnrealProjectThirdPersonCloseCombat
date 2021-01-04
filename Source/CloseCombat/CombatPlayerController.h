// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <Blueprint/UserWidget.h>
#include "CombatPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CLOSECOMBAT_API ACombatPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> hudInstance;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> winInstance;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> loseInstance;

	UUserWidget* hud;
	UUserWidget* winScreen;
	UUserWidget* loseScreen;
public:
	virtual void GameHasEnded(class AActor* EndGameFocus, bool bIsWinner);
};
