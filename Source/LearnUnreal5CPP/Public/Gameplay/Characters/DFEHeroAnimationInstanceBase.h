// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DFEHeroAnimationInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUNREAL5CPP_API UDFEHeroAnimationInstanceBase : public UAnimInstance
{
	GENERATED_BODY()

	UPROPERTY()
	class ADFEHeroCharacter* CharacterRef;

protected:
	UPROPERTY(BlueprintReadWrite, Category="HeroAnimationData")
	bool bIsAccelerating;
	UPROPERTY(BlueprintReadWrite, Category="HeroAnimationData")
	float Speed;
	UPROPERTY(BlueprintReadWrite, Category="HeroAnimationData")
	int32 ComboStack;
	UPROPERTY(BlueprintReadWrite, Category="HeroAnimationData")
	bool bIsChanneling;

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION()
	void AnimNotify_SaveAttack();
	UFUNCTION()
	void AnimNotify_ResetCombo();
};
