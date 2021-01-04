// Copyright Epic Games, Inc. All Rights Reserved.

#include "CloseCombatGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "CombatPlayerController.h"

void ACloseCombatGameModeBase::PawnKilled(bool isPlayer)
{
	ACombatPlayerController* playerCon = Cast<ACombatPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	playerCon->GameHasEnded(nullptr, !isPlayer);
}