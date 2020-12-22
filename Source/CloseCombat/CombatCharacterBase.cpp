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
	movingDeltaTime = DeltaTime;

	if (isAttackPressed)
	{
		lastTimeAttackPressed += DeltaTime;
		if (lastTimeAttackPressed > attackAnims[attackMod]->GetPlayLength())
		{
			isAttackPressed = false;
		}
	}

}

// Called to bind functionality to input
void ACombatCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACombatCharacterBase::MoveVertical);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACombatCharacterBase::MoveHorizontal);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ACombatCharacterBase::Attack);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Repeat, this , &ACombatCharacterBase::Attack);

}

void ACombatCharacterBase::MoveVertical(float pInputValue)
{
	isVerticallyMoving = (pInputValue != 0) ? true : false;
	vertical += pInputValue * movingDeltaTime;
	vertical = FMath::Clamp(vertical, -1.f, 1.f);
}

void ACombatCharacterBase::MoveHorizontal(float pInputValue)
{
	isHorizontallyMoving = (pInputValue != 0) ? true : false;
	horizontal += pInputValue * movingDeltaTime;
	horizontal = FMath::Clamp(horizontal, -1.f, 1.f);
}

void ACombatCharacterBase::Attack()
{
	//처음 누른 것이냐 아닌것이냐
	//다음 공격 쿨타임이냐 아니냐


	if (isAttackPressed && lastTimeAttackPressed > attackAnims[attackMod]->GetPlayLength() * 0.6f)
	{
		PlayAnimMontage(attackAnims[attackMod], 1.f);
		lastTimeAttackPressed = 0.f;
		attackMod++;
		if (attackMod > 2)
		{
			attackMod = 0;
		}
	}
	else if(!isAttackPressed)
	{
		isAttackPressed = true;
		attackMod = 0;
		lastTimeAttackPressed = 0.f;
		PlayAnimMontage(attackAnims[attackMod], 1.f);
	}
}

float ACombatCharacterBase::GetHorizontalMoving() const
{
	return horizontal;
}

float ACombatCharacterBase::GetVerticalMoving() const
{
	return vertical;
}

bool ACombatCharacterBase::IsAttacking() const
{
	return isAttackPressed;
}
