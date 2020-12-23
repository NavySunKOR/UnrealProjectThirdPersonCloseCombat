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

	if (IsInCombat() || IsDead())
	{
		LockMovement();
	}

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

float ACombatCharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	UE_LOG(LogTemp, Warning, TEXT("Damage taken! amount : %f"), Damage);
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	curHp -= Damage;

	UE_LOG(LogTemp, Warning, TEXT("Curhp amount : %f"), curHp);
	if (curHp <= 0.f)
	{
		Dead();
	}

	return Damage;
}

// Called to bind functionality to input
void ACombatCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACombatCharacterBase::MoveVertical);
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACombatCharacterBase::MoveHorizontal);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &ACombatCharacterBase::Attack);
	PlayerInputComponent->BindAction(TEXT("LockOn"), EInputEvent::IE_Pressed, this, &ACombatCharacterBase::LockOn);
	PlayerInputComponent->BindAction(TEXT("Block"), EInputEvent::IE_Pressed, this, &ACombatCharacterBase::BlockOn);
	PlayerInputComponent->BindAction(TEXT("Block"), EInputEvent::IE_Released, this, &ACombatCharacterBase::BlockOff);
	PlayerInputComponent->BindAction(TEXT("TEST_Action"), EInputEvent::IE_Pressed, this, &ACombatCharacterBase::TEST_Action);

}

void ACombatCharacterBase::MoveVertical(float pInputValue)
{
	if (!IsInCombat() && !IsDead())
	{
		isVerticallyMoving = (pInputValue != 0) ? true : false;
		vertical += pInputValue * movingDeltaTime;
		vertical = FMath::Clamp(vertical, -1.f, 1.f);
	}
}

void ACombatCharacterBase::MoveHorizontal(float pInputValue)
{
	if (!IsInCombat() && !IsDead())
	{
		isHorizontallyMoving = (pInputValue != 0) ? true : false;
		horizontal += pInputValue * movingDeltaTime;
		horizontal = FMath::Clamp(horizontal, -1.f, 1.f);
	}
}

void ACombatCharacterBase::Attack()
{
	if (!IsDead())
	{
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
		else if (!IsInCombat())
		{
			isAttackPressed = true;
			attackMod = 0;
			lastTimeAttackPressed = 0.f;
			PlayAnimMontage(attackAnims[attackMod], 1.f);
		}
	}
}

void ACombatCharacterBase::LockOn()
{
	isLockOn = !isLockOn;
	UE_LOG(LogTemp, Warning, TEXT("VOO : %d"), isLockOn);
}

void ACombatCharacterBase::BlockOn()
{
	if (!IsInCombat() && !IsDead())
	{
		isBlocking = true;
		PlayAnimMontage(blockAnim, 1.f);
	}
}

void ACombatCharacterBase::BlockOff()
{
	isBlocking = false;
	StopAnimMontage(blockAnim);
}

void ACombatCharacterBase::LockMovement()
{
	isVerticallyMoving = false;
	isHorizontallyMoving = false;
	vertical = 0.f;
	horizontal = 0.f;
}

void ACombatCharacterBase::TEST_Action()
{
	//자살로직
	FDamageEvent events;
	TakeDamage(100.f, events, GetController(), GetOwner());
}

float ACombatCharacterBase::GetHorizontalMoving() const
{
	return horizontal;
}

float ACombatCharacterBase::GetVerticalMoving() const
{
	return vertical;
}

bool ACombatCharacterBase::IsInCombat() const
{
	return isAttackPressed || isBlocking;
}

bool ACombatCharacterBase::IsLockOn() const
{
	return isLockOn;
}

bool ACombatCharacterBase::IsDead() const
{
	return curHp <= 0.f;
}

void ACombatCharacterBase::Dead()
{
	UE_LOG(LogTemp, Warning, TEXT("Im dying"));
	curHp = 0.f;
	PlayAnimMontage(deadAnim,1.f);
	isDead = true;
}
