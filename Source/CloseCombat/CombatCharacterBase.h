// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CombatCharacterBase.generated.h"

UCLASS()
class CLOSECOMBAT_API ACombatCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveVertical(float pInputValue);
	void MoveHorizontal(float pInputValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	UFUNCTION(BlueprintPure)
	float GetHorizontalMoving() const;
	UFUNCTION(BlueprintPure)
	float GetVerticalMoving() const;



private:
	UPROPERTY(EditAnywhere)
	float horizontal;
	UPROPERTY(EditAnywhere)
	float vertical;
	bool isVerticallyMoving = false;
	bool isHorizontallyMoving = false;
	float deltaTime;
};
