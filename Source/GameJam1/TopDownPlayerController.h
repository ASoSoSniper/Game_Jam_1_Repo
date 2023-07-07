// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacter.h"
#include "TopDownPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM1_API ATopDownPlayerController : public APlayerController
{
	GENERATED_BODY()
		ATopDownPlayerController();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	APlayerCharacter* player;
	ACameraActor* camera;

};
