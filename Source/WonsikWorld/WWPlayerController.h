// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WWPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WONSIKWORLD_API AWWPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	//Chat
	UFUNCTION(BlueprintImplementableEvent, Category = "Chat")
	void RecvChatMessage(const FString& ID,const FString& ChatMessage);
};
