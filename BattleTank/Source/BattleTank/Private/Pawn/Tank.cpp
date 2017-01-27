// Copyright TempleGames GmbH

#include "BattleTank.h"
#include "Component/TankAimingComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("[%s] 4b1167a1: TankC++_Construction"), *GetName());
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

void ATank::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("[%s] 4b1167a1: TankC++_BeginPlay"), *GetName());
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* InputComponentParam)
{
	Super::SetupPlayerInputComponent(InputComponentParam);

}

