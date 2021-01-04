// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Runtime/Engine/Classes/Components/BoxComponent.h>
#include "GameFramework/Character.h"
#include "CombatCharacterBase.generated.h"

UCLASS()
class CLOSECOMBAT_API ACombatCharacterBase : public ACharacter
{
	GENERATED_BODY()

	DECLARE_DELEGATE_OneParam(FIsLockOn, bool);

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
	AActor* lockedOnActor;

	//가드
	bool isBlocking;
	bool isParry;
	UPROPERTY(EditAnywhere)
	UAnimMontage* blockAnim;



	//스탯
	float curHp = 100.f;
	float maxHp = 100.f;
	float damage = 15.f;
	UPROPERTY(EditAnywhere)
	float movementSpeed = 5.f;
	float movementMultiplyer = 1.f;
	
	//피격
	UPROPERTY(EditAnywhere)
	UAnimMontage* hitAnim;

	//사망
	bool isDead = false;
	UPROPERTY(EditAnywhere)
	UAnimMontage* deadAnim;


	//사운드 소스와 컴포넌트
	UPROPERTY(EditAnywhere)
	USoundBase* movingSoundSource;
	UPROPERTY(EditAnywhere)
	USoundBase* attackSoundSource;	
	UPROPERTY(EditAnywhere)
	USoundBase* parrySoundSource;
	UPROPERTY(EditAnywhere)
	USoundBase* guardSoundSource;
	UPROPERTY(EditAnywhere)
	USoundBase* hitSoundSource;
	UPROPERTY(EditAnywhere)
	USoundBase* deadSoundSource;

	UAudioComponent* movingSound;
	UAudioComponent* attackSound;
	UAudioComponent* parrySound;
	UAudioComponent* guardSound;
	UAudioComponent* hitSound;
	UAudioComponent* deadSound;

	//파티클
	UPROPERTY(EditAnywhere)
	UParticleSystem* hitParticle;
	UPROPERTY(EditAnywhere)
	UParticleSystem* parryParticle;

	FTimerHandle timeHandler;

	//Controller
	bool isPlayer;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//외부로 나갈 수 있는 코드들
	void RotateVertical(float pInputValue);
	void RotateHorizontal(float pInputValue);

	//내부적으로 사용하는 코드들
private:
	void LockMovement();
	void CancelAttack();
	void AttackInternal();
	void SetParry(bool pIsParry);
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
	UFUNCTION()
	bool IsBlocking() const;
	UFUNCTION()
	bool IsParry() const;
	UFUNCTION(BlueprintPure)
	float GetCurrentHealth() const;
	UFUNCTION(BlueprintPure)
	float GetHealthPercentage() const;

	void LockOn(bool pIsLockOn);
	void Dead();
	void Attack();
	void BlockOn();
	void BlockOff();
	void MoveVertical(float pInputValue);
	void MoveHorizontal(float pInputValue);
};
