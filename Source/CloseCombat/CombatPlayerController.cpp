// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatPlayerController.h"
#include <Engine/Public/TimerManager.h>


void ACombatPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	hud = CreateWidget(this, hudInstance);

	hud->AddToPlayerScreen(0);
}

void ACombatPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	hud->RemoveFromViewport();
	if (bIsWinner)
	{
		winScreen = CreateWidget(this, winInstance);
		winScreen->AddToPlayerScreen();
	}
	else
	{
		loseScreen = CreateWidget(this, loseInstance);
		loseScreen->AddToPlayerScreen();
	}
	FTimerHandle timer;
	GetWorldTimerManager().SetTimer(timer,this, &APlayerController::RestartLevel,5.f);
}
