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

	//����
	bool isVerticallyMoving = false;
	bool isHorizontallyMoving = false;
	float movingDeltaTime;

	//����
	int attackMod;
	bool isAttackPressed;
	float lastTimeAttackPressed = 0.f;
	UPROPERTY(EditAnywhere)
	UAnimMontage* attackAnims[3];



	//����
	bool isLockOn;
	AActor* lockedOnActor;

	//����
	bool isBlocking;
	bool isParry;
	UPROPERTY(EditAnywhere)
	UAnimMontage* blockAnim;



	//����
	float curHp = 100.f;
	float maxHp = 100.f;
	float damage = 15.f;
	UPROPERTY(EditAnywhere)
	float movementSpeed = 5.f;
	float movementMultiplyer = 1.f;
	
	//�ǰ�
	UPROPERTY(EditAnywhere)
	UAnimMontage* hitAnim;

	//���
	bool isDead = false;
	UPROPERTY(EditAnywhere)
	UAnimMontage* deadAnim;


	//���� �ҽ��� ������Ʈ
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

	//��ƼŬ
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

	//�ܺη� ���� �� �ִ� �ڵ��
	void RotateVertical(float pInputValue);
	void RotateHorizontal(float pInputValue);

	//���������� ����ϴ� �ڵ��
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
