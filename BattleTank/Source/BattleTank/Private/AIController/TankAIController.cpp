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

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerTank)
	{
		// TODO: check radius is in cm
		// Move actor does some path-finding logic and then calls RequestDirectMove on the UNavMovementComponent
		MoveToActor(PlayerTank, AcceptancRadius);

		auto ControlledTank = Cast<ATank>(GetPawn());

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}
}