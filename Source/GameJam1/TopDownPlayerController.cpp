// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownPlayerController.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ATopDownPlayerController::ATopDownPlayerController()
{
	
}

void ATopDownPlayerController::BeginPlay()
{
	camera = Cast<ACameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass()));
	SetViewTarget(camera);
	player = Cast<APlayerCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCharacter::StaticClass()));
}

void ATopDownPlayerController::Tick(float DeltaTime)
{
	RotatePlayer(DeltaTime);
}

void ATopDownPlayerController::RotatePlayer(float& DeltaTime)
{
	FVector mousePosition, mouseDirection;
	const bool bSuccess = DeprojectMousePositionToWorld(mousePosition, mouseDirection);

	if (bSuccess && player)
	{
		FVector playerLocation = player->GetActorLocation();
		FVector endLocation = FMath::LinePlaneIntersection(mousePosition, mousePosition + (mouseDirection * 2000.f), playerLocation, FVector(0, 0, 1));

		FRotator newRotation = UKismetMathLibrary::FindLookAtRotation(player->GetActorLocation(), endLocation);
		FRotator playerRotation = player->GetActorRotation();
		FRotator targetRot = FRotator(playerRotation.Pitch, newRotation.Yaw, playerRotation.Roll);
		//FRotator step = FMath::RInterpTo(playerRotation, targetRot, DeltaTime, 50.f);
		player->SetActorRotation(targetRot);
	}
}
