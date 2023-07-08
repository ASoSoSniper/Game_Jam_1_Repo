// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Health.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	camera = Cast<ACameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass()));
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
}

void APlayerCharacter::MoveRight(float axis)
{
	FRotator controlRot = GetControlRotation();
	FVector newDirection;
	if (camera)
		newDirection = camera->GetActorRightVector();
	
	AddMovementInput(newDirection, axis);
}

void APlayerCharacter::MoveForward(float axis)
{
	FVector Forward;
	if (camera)
		Forward = camera->GetActorRotation().Vector();
	
	FVector projectedForward = Forward.VectorPlaneProject(Forward, FVector(0, 0, 1));
	FVector normalized = projectedForward.GetSafeNormal();

	AddMovementInput(normalized, axis);
}

void APlayerCharacter::Attack()
{
	FVector forward = GetActorForwardVector() * attackDistance;
	
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(attackHitResult, GetActorLocation(), GetActorLocation() + forward, ECC_Visibility, params);

	if (attackHitResult.GetActor())
	{
		if (attackHitResult.GetActor()->ActorHasTag("Enemy"))
		{
			UHealth* targetStats = Cast<UHealth>(attackHitResult.GetActor()->FindComponentByClass(UHealth::StaticClass()));
			if (targetStats)
			{
				//FVector direction = attackHitResult.GetActor()->GetActorLocation() - GetOwner()->GetActorLocation();
				targetStats->HealthChange(-attackDamage);
				targetStats->KnockBack(-attackHitResult.ImpactNormal * knockbackStrength);
			}

			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Enemy has %f health"), targetHealth->HP));
		}
	}
	
	//Debug things
	DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + forward, FColor::Red, false, 0.5f);
	
}



