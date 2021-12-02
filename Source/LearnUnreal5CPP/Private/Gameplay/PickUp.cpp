// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/PickUp.h"

// Sets default values
APickUp::APickUp()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PickUpCollision = CreateDefaultSubobject<USphereComponent>(FName(TEXT("PickUpCollision")));
	SetRootComponent(PickUpCollision);
	
	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("PickUpMesh")));
	PickUpMesh->SetupAttachment(GetRootComponent());
}

FText APickUp::GetPickUpName() const
{
	return PickUpName;
}

void APickUp::SetPickUpName(FText NewName)
{
	PickUpName = NewName;
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

