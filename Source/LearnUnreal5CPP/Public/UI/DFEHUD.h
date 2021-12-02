// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DFEHUD.generated.h"

/**
 * 
 */
UCLASS()
class LEARNUNREAL5CPP_API ADFEHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UDFEPlayerCharacterDataUI> PlayerStatusWidget;

private:
	UPROPERTY()
	UDFEPlayerCharacterDataUI* PlayerStatusComponent;
};
