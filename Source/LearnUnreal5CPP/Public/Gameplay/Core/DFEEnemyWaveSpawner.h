// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Gameplay/Characters/DFEHeroCharacter.h"
#include "DFEEnemyWaveSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEncounterBeginSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEncounterEndSignature);

USTRUCT(BlueprintType)
struct FEnemyWaveMonsterData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TSubclassOf<class ADFECharacterCarcass> Type;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	uint8 Number;	
};

USTRUCT(BlueprintType)
struct FEnemyWave : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	TArray<FEnemyWaveMonsterData> WaveContent;
	// This property will be used with the RowName member inherited from
	// FTableRowBase in order to tell the narrative-handling class which
	// Event should happen.
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	bool bTriggersNarrativeEvent = false;
};

UCLASS()
class LEARNUNREAL5CPP_API ADFEEnemyWaveSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ADFEEnemyWaveSpawner();
	bool NextWave();
	int RemainingWaves();
	UFUNCTION(BlueprintNativeEvent)
	void StartEncounter();
	UFUNCTION(BlueprintNativeEvent)
	void FinishEncounter();

	virtual void Tick(float DeltaTime) override;

	// Fired when the Encounter begins (when the hero enters the EncounterArea)
	FOnEncounterBeginSignature OnEncounterBegin;
	// Fired when the Hero defeats all waves, effectively ending the Encounter. 
	FOnEncounterEndSignature OnEncounterEnd;

	UFUNCTION()
	void HandleEnemyDeath();
	UFUNCTION()
	void HandlePlayerEnter(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UBoxComponent* EncounterArea;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UBoxComponent* EncounterGateA;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UBoxComponent* EncounterGateB;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="WaveConfiguration")
	TSubclassOf<ADFECharacterBase> ExpectedPlayerClass = ADFEHeroCharacter::StaticClass();
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="WaveConfiguration")
	TArray<FEnemyWave> Waves;
	
private:
	int CurrentWave = 0;
	TArray<ADFECharacterCarcass*> ActiveEnemies;
	bool bIsEncounterActive = false;
	// Spawns a new wave based on the provided FEnemyWave data structure
	void SpawnEnemyWave(FEnemyWave Wave);
};
