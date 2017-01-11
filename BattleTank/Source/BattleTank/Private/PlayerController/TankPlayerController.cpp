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

	FVector HitLocation(ForceInitToZero);
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		// TODO: tell controlled tank to aim at this point
	}
}

// Get world location of line trace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation( FVector& HitLocation ) const
{
	// Find the crosshair position
	int ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection(ForceInitToZero);
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that look direction, and see what we hit (up to max range)
		FHitResult RV_Hit(ForceInit);
		if (GetLookVectorHitLocation(RV_Hit, ScreenLocation, LookDirection))
		{
			HitLocation = RV_Hit.Location;
			return true;
		}
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldlocation(ForceInitToZero);	// To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldlocation,
		LookDirection
		);
}

bool ATankPlayerController::GetLookVectorHitLocation(FHitResult &RV_Hit, FVector2D& ScreenLocation, FVector& Direction) const
{
	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, GetControlledTank());
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = false;
	RV_TraceParams.bReturnPhysicalMaterial = false;

	UCameraComponent* CameraComponent = Cast<UCameraComponent>(GetControlledTank()->GetComponentByClass(UCameraComponent::StaticClass()));
	FVector Start(ScreenLocation.X, ScreenLocation.Y, CameraComponent->GetComponentLocation().Z);
	FVector End = Start + (Direction * LineTraceRange);

	return GetWorld()->LineTraceSingleByChannel(
		RV_Hit,			//result
		Start,			//start
		End,			//end
		ECC_Visibility, //collision channel
		RV_TraceParams
		);
}
