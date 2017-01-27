// Copyright TempleGames GmbH

#include "BattleTank.h"
#include "Component/TankAimingComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector Hitlocation)
{
	auto TankAimingComponent = GetTankAimingComponent();
	if (TankAimingComponent)
	{
		TankAimingComponent->AimAt(Hitlocation);
	}
}

void ATank::Fire()
{
	auto TankAimingComponent = GetTankAimingComponent();
	if (TankAimingComponent)
	{
		TankAimingComponent->Fire();
	}
}

UTankAimingComponent* ATank::GetTankAimingComponent() const
{
	return Cast<UTankAimingComponent>(GetComponentByClass(UTankAimingComponent::StaticClass()));
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* InputComponentParam)
{
	Super::SetupPlayerInputComponent(InputComponentParam);

}

