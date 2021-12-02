// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Characters/DFEHeroAnimationInstanceBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Gameplay/Characters/DFEHeroCharacter.h"

void UDFEHeroAnimationInstanceBase::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	APawn* Owner = TryGetPawnOwner();

	if(Owner)
	{
		CharacterRef = CastChecked<ADFEHeroCharacter>(Owner);
	}
}

void UDFEHeroAnimationInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(CharacterRef)
	{
		bIsAccelerating = CharacterRef->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0;
		Speed = CharacterRef->GetVelocity().Size();
	}
}

void UDFEHeroAnimationInstanceBase::AnimNotify_SaveAttack()
{
	CharacterRef->QueueCombo();
}

void UDFEHeroAnimationInstanceBase::AnimNotify_ResetCombo()
{
	CharacterRef->ResetCombo();
}
