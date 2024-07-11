// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidgetBlueprint.h"
#include "WWMainMenuBox.generated.h"

/**
 * 
 */
UCLASS()
class WONSIKWORLD_API UWWMainMenuBox : public UUserWidgetBlueprint
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Error")
	void ShowError(const FString& ID);
};
