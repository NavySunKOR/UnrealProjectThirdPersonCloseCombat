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


private:
	UPROPERTY(EditAnywhere)
		float horizontal;
	UPROPERTY(EditAnywhere)
		float vertical;

	//무빙
	bool isVerticallyMoving = false;
	bool isHorizontallyMoving = false;
	float movingDeltaTime;

	//공격
	int attackMod;
	bool isAttackPressed;
	float lastTimeAttackPressed = 0.f;
	UPROPERTY(EditAnywhere)
		UAnimMontage* attackAnims[3];


	//락온
	bool isLockOn;

	//가드
	bool isBlocking;
	UPROPERTY(EditAnywhere)
	UAnimMontage* blockAnim;

	//스탯
	float curHp = 100.f;
	float maxHp = 100.f;
	float damage = 15.f;
	
	//사망
	bool isDead = false;
	UPROPERTY(EditAnywhere)
	UAnimMontage* deadAnim;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//외부로 나갈 수 있는 코드들
	void MoveVertical(float pInputValue);
	void MoveHorizontal(float pInputValue);
	void Attack();
	void LockOn();
	void BlockOn();
	void BlockOff();

	//내부적으로 사용하는 코드들
private:
	void LockMovement();
	void TEST_Action();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	

	// Called to bind functionality to input
	UFUNCTION(BlueprintPure)
	float GetHorizontalMoving() const;
	UFUNCTION(BlueprintPure)
	float GetVerticalMoving() const;
	UFUNCTION(BlueprintPure)
	bool IsInCombat() const;
	UFUNCTION(BlueprintPure)
	bool IsLockOn() const;
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	void Dead();
};
