// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

ATopDownPlayerController::ATopDownPlayerController()
{
	
}

void ATopDownPlayerController::BeginPlay()
{
	camera = Cast<ACameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass()));
	SetViewTarget(camera);
	
}
