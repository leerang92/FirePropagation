// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FirePropagationGameMode.h"
#include "FirePropagationHUD.h"
#include "FirePropagationCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFirePropagationGameMode::AFirePropagationGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFirePropagationHUD::StaticClass();
}
