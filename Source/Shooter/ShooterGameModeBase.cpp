// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShooterGameModeBase.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"

AShooterGameModeBase::AShooterGameModeBase()
{
	DefaultPawnClass = AMyCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}