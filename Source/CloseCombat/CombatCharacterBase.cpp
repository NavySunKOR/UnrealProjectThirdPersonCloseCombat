// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCharacterBase.h"
#include <Runtime/Engine/Public/EngineUtils.h>
#include <Runtime/Engine/Classes/Components/BoxComponent.h>
#include <Runtime/Engine/Classes/Components/AudioComponent.h>
#include <Runtime/Engine/Classes/Particles/ParticleSystemComponent.h>
#include <Kismet/GameplayStatics.h>
#include <typeinfo>

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
	movingSound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), movingSoundSource,GetActorLocation());
	movingSound->Stop();
	attackSound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), attackSoundSource, GetActorLocation());
	attackSound->Stop();
	parrySound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), parrySoundSource, GetActorLocation());
	parrySound->Stop();
	guardSound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), guardSoundSource, GetActorLocation());
	guardSound->Stop();
	hitSound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), hitSoundSource, GetActorLocation());
	hitSound->Stop();
	deadSound = UGameplayStatics::SpawnSoundAtLocation(GetWorld(), deadSoundSource, GetActorLocation());
	deadSound->Stop();
}

// Called every frame
void ACombatCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsInCombat() || IsDead())
	{
		LockMovement();
	}


	movingDeltaTime = DeltaTime * 5.f;

	if (!isVerticallyMoving)
	{
		if (vertical > 0.f)
		{
			vertical -= movingDeltaTime;
			vertical = (vertical < 0.f) ? 0.f : vertical;
		}
		
		if( vertical < 0.f)
		{
			vertical += movingDeltaTime;
			vertical = (vertical > 0.f) ? 0.f : vertical;
		}

	
	}

	if (!isHorizontallyMoving)
	{
		if (horizontal > 0.f)
		{
			horizontal -= movingDeltaTime;
			horizontal = (horizontal < 0.f) ? 0.f : horizontal;
		}

		if (horizontal < 0.f)
		{
			horizontal += movingDeltaTime;
			horizontal = (horizontal > 0.f) ? 0.f : horizontal;
		}
	}

	if ((vertical < 0.1f && vertical >-0.1f)
		&& (horizontal < 0.1f && horizontal >-0.1f))
	{
		if (movingSound->IsPlaying())
			movingSound->Stop();
	}
	else
	{
		movingSound->SetWorldLocation(GetActorLocation());
		if (!movingSound->IsPlaying())
			movingSound->Play();
	}

	if (isAttackPressed)
	{
		lastTimeAttackPressed += DeltaTime;
		if (lastTimeAttackPressed > attackAnims[attackMod]->GetPlayLength())
		{
			isAttackPressed = false; 
			CancelAttack();
		}
	}

	if (isLockOn && lockedOnActor != nullptr)
	{
		FRotator lookRotation = (lockedOnActor->GetActorLocation() - GetActorLocation()).Rotation();
		lookRotation.Roll = 0.f;
		lookRotation.Pitch = 0.f;
		SetActorRotation(lookRotation);
	}
}

float ACombatCharacterBase::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	hitSound->SetWorldLocation(GetActorLocation());
	hitSound->Play();
	curHp -= Damage;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitParticle, GetActorLocation());

	PlayAnimMontage(hitAnim, 1.f);
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
		CancelAttack();
		isVerticallyMoving = (pInputValue != 0) ? true : false;
		vertical += pInputValue * movingDeltaTime ;
		vertical = FMath::Clamp(vertical, -movementMultiplyer, movementMultiplyer);
		AddMovementInput(GetActorForwardVector() * vertical * movementSpeed);
	}
}

void ACombatCharacterBase::MoveHorizontal(float pInputValue)
{
	if (!IsInCombat() && !IsDead())
	{
		CancelAttack();
		isHorizontallyMoving = (pInputValue != 0) ? true : false;
		horizontal += pInputValue * movingDeltaTime;
		horizontal = FMath::Clamp(horizontal, -movementMultiplyer, movementMultiplyer);
		AddMovementInput(GetActorRightVector() * horizontal * movementSpeed );
	}
}

void ACombatCharacterBase::Attack()
{
	if (!IsDead())
	{
		if (isAttackPressed && lastTimeAttackPressed > attackAnims[attackMod]->GetPlayLength() * 0.4f)
		{
			GetWorldTimerManager().SetTimer(timeHandler, this, &ACombatCharacterBase::AttackInternal, attackAnims[attackMod]->GetPlayLength() * 0.1f, false);
			attackSound->SetWorldLocation(GetActorLocation());
			attackSound->Play();
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
			GetWorldTimerManager().SetTimer(timeHandler, this, &ACombatCharacterBase::AttackInternal, attackAnims[attackMod]->GetPlayLength() * 0.1f, false);
			attackSound->SetWorldLocation(GetActorLocation());
			attackSound->Play();
			PlayAnimMontage(attackAnims[attackMod], 1.f);
		}
		
	}
}

void ACombatCharacterBase::LockOn()
{
	isLockOn = !isLockOn;
	movementMultiplyer = (isLockOn) ? 0.5f : 1.f;
	
	if (isLockOn)
	{
		TActorRange<AActor> actorsInWorld = TActorRange<AActor>(GetWorld());
		for (AActor* act : actorsInWorld)
		{
			UE_LOG(LogTemp, Warning, TEXT("Name : %s"), *act->GetActorLabel());
			
			if (act != this && act->GetActorLabel().Equals(TEXT("BP_CombatCharacterBase")))
			{
				//락온
				UE_LOG(LogTemp, Warning, TEXT("TargetFound!"));
				lockedOnActor = act;
			}
		}
	}
	else
	{
		lockedOnActor = nullptr;
	}


	UE_LOG(LogTemp, Warning, TEXT("VOO : %d"), isLockOn);
}

void ACombatCharacterBase::BlockOn()
{
	if (!IsInCombat() && !IsDead())
	{
		isBlocking = true;
		GetWorldTimerManager().SetTimer(timeHandler,this, &ACombatCharacterBase::SetParry, blockAnim->GetPlayLength()*0.1f, false);
		GetWorldTimerManager().SetTimer(timeHandler, this, &ACombatCharacterBase::SetParry, blockAnim->GetPlayLength()*0.2f, false);
		PlayAnimMontage(blockAnim, 1.f);

		guardSound->SetWorldLocation(GetActorLocation());
		guardSound->Play();
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

void ACombatCharacterBase::CancelAttack()
{
	for (int i = 0; i < 3; i++)
	{
		StopAnimMontage(attackAnims[i]);
	}
}

void ACombatCharacterBase::AttackInternal()
{
	FHitResult hit;
	FVector start = GetActorLocation();
	FVector end = GetActorLocation() + GetActorForwardVector() * 100.f;
	FCollisionQueryParams param;
	param.AddIgnoredActor(this);
	FName tag("MyTraceTag");
	GetWorld()->DebugDrawTraceTag = tag;
	param.TraceTag = tag;

	UE_LOG(LogTemp, Warning, TEXT("Attack!"));
	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_Pawn, param))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit! : %s"),*hit.GetActor()->GetActorLabel());
		ACombatCharacterBase* hitActor = Cast<ACombatCharacterBase>(hit.GetActor());
		if (hitActor != nullptr)
		{
			//패리중이면
			if (hitActor->IsParry())
			{
				FDamageEvent damageEvent;
				TakeDamage(damage/3.f, damageEvent, GetController(), GetOwner());
				parrySound->SetWorldLocation(GetActorLocation());
				parrySound->Play();
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), parryParticle, GetActorLocation());
			}
			//가드를 안올리고 있으면
			else if (!hitActor->IsBlocking())
			{
				FDamageEvent damageEvent;
				hitActor->TakeDamage(damage, damageEvent, GetController(), GetOwner());
			}
		}
	}
}

void ACombatCharacterBase::SetParry()
{
	isParry = !isParry;
}

void ACombatCharacterBase::TEST_Action()
{
	//자살로직
	FDamageEvent events;
	TakeDamage(15.f, events, GetController(), GetOwner());
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

bool ACombatCharacterBase::IsBlocking() const
{
	return isBlocking;
}

bool ACombatCharacterBase::IsParry() const
{
	return isParry;
}

float ACombatCharacterBase::GetCurrentHealth() const
{
	return curHp;
}

float ACombatCharacterBase::GetHealthPercentage() const
{
	return curHp/maxHp;
}

void ACombatCharacterBase::Dead()
{
	UE_LOG(LogTemp, Warning, TEXT("Im dying"));
	curHp = 0.f;
	deadSound->SetWorldLocation(GetActorLocation());
	deadSound->Play();
	PlayAnimMontage(deadAnim,1.f);
	isDead = true;
}
