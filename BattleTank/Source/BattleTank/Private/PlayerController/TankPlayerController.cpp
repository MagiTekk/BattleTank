// Copyright TempleGames GmbH

#include "BattleTank.h"
#include "Component/TankAimingComponent.h"
#include "Pawn/Tank.h"
#include "TankPlayerController.h"

ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AutoComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AutoComponent)) { return; }
	FoundAimingComponent(AutoComponent);
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrossHair();
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// Subscribe our local method to the tank's death event
		// We do this here since in the constructor could be too early and BeginPlay may not have a Possessed Tank
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
	}
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetPawn()) {return;}
	
	FVector HitLocation(0);
	if (GetSightRayHitLocation(HitLocation))
	{
		auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(AimingComponent)) { return; }

		AimingComponent->AimAt(HitLocation);
	}
}

// Get world location of line trace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation( FVector& HitLocation ) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection(0);
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that look direction, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldlocation(0);	// To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldlocation,
		LookDirection
		);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
		))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

void ATankPlayerController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("** ATankPlayerController::OnTankDeath **"));
}
