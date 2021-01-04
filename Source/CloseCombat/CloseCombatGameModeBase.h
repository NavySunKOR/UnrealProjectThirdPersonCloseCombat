// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CloseCombatGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CLOSECOMBAT_API ACloseCombatGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public: 
	void PawnKilled(bool isPlayer);
	
};
