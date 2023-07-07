// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameJam1GameModeBase.h"
#include "PlayerCharacter.h"

AGameJam1GameModeBase::AGameJam1GameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bAllowTickOnDedicatedServer = false;

	DefaultPawnClass = APlayerCharacter::StaticClass();
}