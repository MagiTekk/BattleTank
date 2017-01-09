// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


ATankAIController::ATankAIController()
{

}

ATankAIController::~ATankAIController()
{

}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	// Aim at Player Tank
	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerTank not not found"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Aiming at PlayerTank: %s"), *PlayerTank->GetName());
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