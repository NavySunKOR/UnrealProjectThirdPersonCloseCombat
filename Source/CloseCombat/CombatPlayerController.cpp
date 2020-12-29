// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatPlayerController.h"


void ACombatPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	hud = CreateWidget(this, hudInstance);

	hud->AddToPlayerScreen(0);
}