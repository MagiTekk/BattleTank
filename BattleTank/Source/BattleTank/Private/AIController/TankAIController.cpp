// Copyright TempleGames GmbH

#include "BattleTank.h"
#include "Component/TankAimingComponent.h"
#include "Pawn/Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (ensure(PlayerTank))
	{
		// Move actor does some path-finding logic and then calls RequestDirectMove on the UNavMovementComponent
		MoveToActor(PlayerTank, AcceptancRadius);

		auto ControlledTank = GetPawn();
		if (!ensure(ControlledTank)) { return; }

		// Aim towards the player
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(AimingComponent)) { return; }

		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
		{
			AimingComponent->Fire();
		}
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);

		if (!ensure(PossesedTank)) { return; }

		// Subscribe our local method to the tank's death event
		// We do this here since in the constructor could be too early and BeginPlay may not have a Possessed Tank
		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("** ATankAIController::OnTankDeath **"));
}
