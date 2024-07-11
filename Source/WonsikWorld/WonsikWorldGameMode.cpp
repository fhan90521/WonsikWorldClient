// Copyright Epic Games, Inc. All Rights Reserved.

#include "WonsikWorldGameMode.h"
#include "WonsikWorldCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWonsikWorldGameMode::AWonsikWorldGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
