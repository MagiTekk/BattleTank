// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Pawn/Tank.h"
#include "TankAIController.h"

ATankAIController::ATankAIController()
{

}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		// TODO move towards the player

		// Aim towards the player
		FVector HitLocation = PlayerTank->GetActorLocation();
		GetControlledTank()->AimAt(HitLocation);

		// Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn)
	{
		return nullptr;
	}

	return Cast<ATank>(PlayerPawn);
}