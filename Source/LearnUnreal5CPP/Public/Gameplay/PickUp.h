// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PickUp.generated.h"

UENUM(BlueprintType)
enum class EGameplayItemType : uint8
{
	PickUp,
	PowerUp,
	Weapon,
	Hazard
};

USTRUCT(BlueprintType)
struct FItemGameplayData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText ItemName;
	UPROPERTY(EditAnywhere)
	EGameplayItemType Type;
	UPROPERTY(EditAnywhere)
	float Value;
	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;
};

UCLASS()
class LEARNUNREAL5CPP_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:
	APickUp();

	FText GetPickUpName() const;
	
	void SetPickUpName(FText NewName);

	UPROPERTY(EditAnywhere)
	FItemGameplayData ItemData;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditInstanceOnly, Category="PickUp Data", meta=(AllowPrivateAccess))
	FText PickUpName;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PickUpMesh;

	UPROPERTY(EditAnywhere)
	USphereComponent* PickUpCollision;
};
