// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

ATankPlayerController::~ATankPlayerController()
{

}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Log out Possessed Tank
	ATank* PossesedTank = GetControlledTank();
	if (!PossesedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Possesed Tank: %s"), *PossesedTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrossHair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank())
	{
		return;
	}

	// Get world location through crosshair
	// If it hits the landscape 
		// Tell controlled tank to aim at this point
}