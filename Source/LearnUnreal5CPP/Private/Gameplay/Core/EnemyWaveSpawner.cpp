

#include "Gameplay/Core/DFEEnemyWaveSpawner.h"
#include "Components/BoxComponent.h"
#include "Gameplay/Characters/Carcass/DFECharacterCarcass.h"
#include "Components/PrimitiveComponent.h"
#include "Gameplay/Characters/DFEHeroCharacter.h"

ADFEEnemyWaveSpawner::ADFEEnemyWaveSpawner()
{
 	PrimaryActorTick.bCanEverTick = true;

	EncounterArea = CreateDefaultSubobject<UBoxComponent>(FName("EncounterArea"));
	EncounterArea->SetBoxExtent(FVector(100.f, 100.f, 100.f),false);
	EncounterArea->OnComponentBeginOverlap.AddDynamic(this, &ADFEEnemyWaveSpawner::HandlePlayerEnter);
	SetRootComponent(EncounterArea);

	EncounterGateA = CreateDefaultSubobject<UBoxComponent>(FName("EncounterGateA"));
	EncounterGateA->SetBoxExtent(FVector(100.f, 25.f, 100.f),false);
	EncounterGateA->SetCollisionProfileName(TEXT("NoCollision"));
	EncounterGateA->SetRelativeLocation(FVector(0.f, 150.f, 0.f));
	EncounterGateA->SetupAttachment(EncounterArea);
	
	EncounterGateB = CreateDefaultSubobject<UBoxComponent>(FName("EncounterGateB"));
	EncounterGateB->SetBoxExtent(FVector(100.f, 25.f, 100.f),false);
	EncounterGateB->SetCollisionProfileName(TEXT("NoCollision"));
	EncounterGateB->SetRelativeLocation(FVector(0.f, -150.f, 0.f));
	EncounterGateB->SetupAttachment(EncounterArea);
}

void ADFEEnemyWaveSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADFEEnemyWaveSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADFEEnemyWaveSpawner::HandlePlayerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetClass() == *ExpectedPlayerClass)
	{
		// We've found our player!
		UE_LOG(LogTemp, Warning, TEXT("Starting Ecounter!"));
		StartEncounter();
	}
}

void ADFEEnemyWaveSpawner::HandleEnemyDeath()
{
	if(ActiveEnemies.Num() < 1)
	{
		NextWave();	
	}
}

void ADFEEnemyWaveSpawner::SpawnEnemyWave(FEnemyWave Wave)
{
	if(Wave.WaveContent.Num() > 0)
	{
		for(auto It = Wave.WaveContent.CreateConstIterator(); It; ++It)
		{
			FTransform EnemySpawnPoint;
			EnemySpawnPoint.SetLocation(GetActorLocation());
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			AActor* SpawnedActor = nullptr;
			ADFECharacterCarcass* SpawnedEnemy = nullptr;
			
			for(int i = 0 ; i < It->Number && *It->Type; i++)
			{
				SpawnedActor = GetWorld()->SpawnActor(*It->Type, &EnemySpawnPoint, SpawnParams);
				SpawnedEnemy = CastChecked<ADFECharacterCarcass>(SpawnedActor);
				if(SpawnedEnemy)
				{
					SpawnedEnemy->OnDeath.AddDynamic(this, &ADFEEnemyWaveSpawner::HandleEnemyDeath);
					ActiveEnemies.Add(SpawnedEnemy);
				}
			}
		}
	}
}

bool ADFEEnemyWaveSpawner::NextWave()
{
	if(RemainingWaves() > 0)
	{
		SpawnEnemyWave(Waves[CurrentWave]);
		CurrentWave++;
		return true;
	}

	FinishEncounter();
	return false;
}

int ADFEEnemyWaveSpawner::RemainingWaves()
{
	return Waves.Num() - CurrentWave;
}

void ADFEEnemyWaveSpawner::StartEncounter_Implementation()
{
	if(bIsEncounterActive || RemainingWaves() < 1) return;
	
	bIsEncounterActive = true;
	EncounterGateA->SetCollisionProfileName(TEXT("Pawn"));
	EncounterGateB->SetCollisionProfileName(TEXT("Pawn"));
	EncounterArea->OnComponentBeginOverlap.RemoveDynamic(this, &ADFEEnemyWaveSpawner::HandlePlayerEnter);

	NextWave();
	
	if(OnEncounterBegin.IsBound())
	{
		OnEncounterBegin.Broadcast();
	}
}

void ADFEEnemyWaveSpawner::FinishEncounter_Implementation()
{
	if(bIsEncounterActive)
	{
		bIsEncounterActive = false;
		EncounterGateA->SetCollisionProfileName(TEXT("NoCollision"));
		EncounterGateB->SetCollisionProfileName(TEXT("NoCollision"));

		for(auto It = ActiveEnemies.CreateConstIterator(); It; ++It)
		{
			(*It)->Destroy();
		}

		if(OnEncounterEnd.IsBound())
		{
			OnEncounterEnd.Broadcast();
		}
	}
}
