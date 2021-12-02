// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Characters/DFECharacterBase.h"

ADFECharacterBase::ADFECharacterBase()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void ADFECharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADFECharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADFECharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}

void ADFECharacterBase::ExecuteDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Executing Brute Enemy death logic..."));
}

