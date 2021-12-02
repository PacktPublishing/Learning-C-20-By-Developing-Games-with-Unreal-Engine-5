// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DFEHUD.h"
#include "UI/DFEPlayerCharacterDataUI.h"

void ADFEHUD::BeginPlay()
{
	Super::BeginPlay();

	PlayerStatusComponent = CreateWidget<UDFEPlayerCharacterDataUI>(GetWorld(), PlayerStatusWidget, "PlayerStatus");
	PlayerStatusComponent->AddToViewport();
}
