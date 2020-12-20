// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCharacterBase.h"

// Sets default values
ACombatCharacterBase::ACombatCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACombatCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACombatCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!isVerticallyMoving)
	{
		if (vertical > 0.f)
		{
			vertical -= DeltaTime;
			vertical = (vertical < 0.f) ? 0.f : vertical;
		}
		
		if( vertical < 0.f)
		{
			vertical += DeltaTime;
			vertical = (vertical > 0.f) ? 0.f : vertical;
		}
	}

	if (!isHorizontallyMoving)
	{
		if (horizontal > 0.f)
		{
			horizontal -= DeltaTime;
			horizontal = (horizontal < 0.f) ? 0.f : horizontal;
		}

		if (horizontal < 0.f)
		{
			horizontal += DeltaTime;
			horizontal = (horizontal > 0.f) ? 0.f : horizontal;
		}
	}
	deltaTime = DeltaTime;
}

// Called to bind functionality to input
void ACombatCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACombatCharacterBase::MoveVertical);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACombatCharacterBase::MoveHorizontal);

}

void ACombatCharacterBase::MoveVertical(float pInputValue)
{
	isVerticallyMoving = (pInputValue != 0) ? true : false;
	vertical += pInputValue * deltaTime;
	vertical = FMath::Clamp(vertical, -1.f, 1.f);
}

void ACombatCharacterBase::MoveHorizontal(float pInputValue)
{
	isHorizontallyMoving = (pInputValue != 0) ? true : false;
	horizontal += pInputValue * deltaTime;
	horizontal = FMath::Clamp(horizontal, -1.f, 1.f);
}

float ACombatCharacterBase::GetHorizontalMoving() const
{
	return horizontal;
}

float ACombatCharacterBase::GetVerticalMoving() const
{
	return vertical;
}

