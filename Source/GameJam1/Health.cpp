// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	movementComponent = Cast<UCharacterMovementComponent>(GetOwner()->FindComponentByClass(UCharacterMovementComponent::StaticClass()));
}


// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (stunned && stunTimer > 0.f)
	{
		stunTimer -= DeltaTime;
	}
	else if (stunned && stunTimer <= 0.f)
	{
		if (movementComponent->MovementMode != MOVE_NavWalking)
		{
			stunned = false;
			movementComponent->SetMovementMode(MOVE_NavWalking);
		}
	}
}

void UHealth::HealthChange(int value)
{
	HP += value;
	if (HP <= 0)
	{
		Death();
	}
}

void UHealth::Death()
{
	GetOwner()->Destroy();
}

void UHealth::KnockBack(FVector direction)
{
	if (movementComponent)
	{
		stunned = true;
		stunTimer = stunLength;
		movementComponent->SetMovementMode(MOVE_Custom);

		movementComponent->Launch(FVector(direction.X, direction.Y, 500.f));
		

	}
}

