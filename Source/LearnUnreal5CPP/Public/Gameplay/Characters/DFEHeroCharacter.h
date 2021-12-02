// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/Characters/DFECharacterBase.h"
#include "DFEHeroCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LEARNUNREAL5CPP_API ADFEHeroCharacter : public ADFECharacterBase
{
	GENERATED_BODY()

	uint8 ComboCounter = 0;
	bool bIsAttackQueued = false;
	bool bIsAttacking = false;

	void InvalidateActiveCombo();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	class USpringArmComponent* CameraArm;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="CharacterActions")
	class UAnimMontage* ActionAttack;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="CharacterActions")
	class UAnimMontage* ActionPickUp;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="CharacterActions")
	class UAnimMontage* ActionChannel;

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	ADFEHeroCharacter();

	void Attack();
	void SwitchItem();
	void UseItemStart();
	void UseItemEnd();

	void MoveRight(float Input);
	void MoveUp(float Input);

	void QueueCombo();
	void ResetCombo();
	void ExecuteAttack();
};
