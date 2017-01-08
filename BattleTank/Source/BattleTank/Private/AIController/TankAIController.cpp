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

	// Log out Possesed Tank
	ATank* PossesedTank = GetControlledTank();
	if (!PossesedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possesing a Tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Possesed Tank: %s"), *PossesedTank->GetName());
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}