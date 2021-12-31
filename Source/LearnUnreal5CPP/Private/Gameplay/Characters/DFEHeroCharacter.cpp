// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Characters/DFEHeroCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/AnimMontage.h"
#include "Kismet/GameplayStatics.h"

void ADFEHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADFEHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ADFEHeroCharacter::Attack);
	PlayerInputComponent->BindAction("Switch", IE_Pressed, this, &ADFEHeroCharacter::SwitchItem);
	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &ADFEHeroCharacter::UseItemStart);
	PlayerInputComponent->BindAction("Use", IE_Released, this, &ADFEHeroCharacter::UseItemEnd);

	PlayerInputComponent->BindAxis("MoveRight", this, &ADFEHeroCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ADFEHeroCharacter::MoveUp);
}

ADFEHeroCharacter::ADFEHeroCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CameraArm = CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	CameraArm->TargetArmLength = 500.f;
	CameraArm->SocketOffset = FVector(0.f,0.f,0.f);
	CameraArm->bDoCollisionTest = false;
	CameraArm->SetUsingAbsoluteRotation(true);
	CameraArm->SetRelativeRotation(FRotator(0.f, -20.f, 0.f));
	CameraArm->SetupAttachment(GetRootComponent());
	
	Camera = CreateDefaultSubobject<UCameraComponent>("PlayerCameraComponent");
	Camera->SetupAttachment(CameraArm);
	Camera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
}

void ADFEHeroCharacter::Attack()
{
	if(!GetCharacterMovement()->IsMovementInProgress())
	{		
		if(ActionAttack)
		{
			if(bIsAttacking)
			{
				bIsAttackQueued = true;
			}
			else
			{
				ExecuteAttack();
			}
		}
	}
}

void ADFEHeroCharacter::SwitchItem()
{
	
}

void ADFEHeroCharacter::UseItemStart()
{
	
}

void ADFEHeroCharacter::UseItemEnd()
{
	
}

void ADFEHeroCharacter::MoveRight(float Input)
{
	if(Input != 0.f)
	{
		InvalidateActiveCombo();
		AddMovementInput(FVector::YAxisVector, Input);
	}
}

void ADFEHeroCharacter::MoveUp(float Input)
{
	if(Input != 0.f)
	{
		InvalidateActiveCombo();
		AddMovementInput(FVector::XAxisVector, Input);
	}
}

void ADFEHeroCharacter::QueueCombo()
{
	UE_LOG(LogTemp, Warning, TEXT("[DFEHero] Combo: Queued"));
	
	if(bIsAttackQueued)
	{
		bIsAttackQueued = false;
		ComboCounter = (ComboCounter + 1) % 3 ;
		ExecuteAttack();
	}
	else
	{
		bIsAttackQueued = true;
	}
}

void ADFEHeroCharacter::ResetCombo()
{
	ComboCounter = 0;
	bIsAttackQueued = false;
	bIsAttacking = false;
}

void ADFEHeroCharacter::InvalidateActiveCombo()
{
	if(ComboCounter > 0)
	{
		StopAnimMontage();
		ResetCombo();
	}
}

void ADFEHeroCharacter::ExecuteAttack()
{
	bIsAttacking = true;
	FString MontageComboSection = "ComboAttack";
	MontageComboSection.AppendInt(ComboCounter);
	PlayAnimMontage(ActionAttack, 1.0f, FName(MontageComboSection));
}

