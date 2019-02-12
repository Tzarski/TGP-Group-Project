// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TestGameMode.h"
#include "TestPlayerController.h"
#include "TestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestGameMode::ATestGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATestPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}