// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/DFEGameMode.h"

#include "Gameplay/DFEPlayerController.h"
#include "Gameplay/Characters/DFEHeroCharacter.h"
#include "UI/DFEHUD.h"
#include "Gameplay/Core/DFEEnemyWaveSpawner.h"
#include "Kismet/GameplayStatics.h"

ADFEGameMode::ADFEGameMode()
{
	DefaultPawnClass = ADFEHeroCharacter::StaticClass();
	PlayerControllerClass = ADFEPlayerController::StaticClass();
	HUDClass = ADFEHUD::StaticClass();

	CurrentDecayWards = StartingDecayWards;
}

void ADFEGameMode::SetActiveWaveSpawner(ADFEEnemyWaveSpawner* Spawner)
{
	CurrentSpawner = Spawner;
}

void ADFEGameMode::LoseDecayWard()
{
	CurrentDecayWards--;
	if(CurrentDecayWards < 0)
	{
		GameOver();
	}
}

void ADFEGameMode::GameOver()
{
	// TODO Remember, this is temporary. The function is an endpoint to execute related code!
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	if(Controller)
	{
		Controller->ConsoleCommand("quit");
	}
}

void ADFEGameMode::StageClear()
{
	UE_LOG(LogTemp, Warning, TEXT("The boss is dead! Stage Clear!"))
}
