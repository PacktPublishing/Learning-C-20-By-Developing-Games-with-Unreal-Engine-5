// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DFEGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUNREAL5CPP_API ADFEGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ADFEGameMode();

	UFUNCTION(BlueprintCallable, Category="DarkFantasyEpic|WaveManagement")
	void SetActiveWaveSpawner(class ADFEEnemyWaveSpawner* Spawner);

	UFUNCTION(BlueprintCallable, Category="DarkFantasyEpic|GameFlow")
	void LoseDecayWard();
	UFUNCTION(BlueprintCallable, Category="DarkFantasyEpic|GameFlow")
	void GameOver();
	UFUNCTION(BlueprintCallable, Category="DarkFantasyEpic|GameFlow")
	void StageClear();

protected:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="DarkFantasyEpic|GameData")
	uint8 StartingDecayWards = 3;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="DarkFantasyEpic|GameData")
	uint8 MaxDecayWards = 5;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="DarkFantasyEpic|GameData")
	int32 DecayWardChargeAmount = 1000;
		
private:

	UPROPERTY()
	ADFEEnemyWaveSpawner* CurrentSpawner;
	uint8 CurrentDecayWards = 0;
	int32 CurrentDecayWardCharge = 0;

};
