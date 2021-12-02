// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/DFEGameMode.h"

#include "Gameplay/DFEPlayerController.h"
#include "Gameplay/Characters/DFEHeroCharacter.h"
#include "UI/DFEHUD.h"

ADFEGameMode::ADFEGameMode()
{
	DefaultPawnClass = ADFEHeroCharacter::StaticClass();
	PlayerControllerClass = ADFEPlayerController::StaticClass();
	HUDClass = ADFEHUD::StaticClass();
}
