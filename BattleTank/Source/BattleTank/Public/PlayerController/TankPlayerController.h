// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pawn/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ATankPlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	ATank* GetControlledTank() const;

private:

	UPROPERTY(EditAnywhere, Category = "UI")
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere, Category = "UI")
		float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere, Category = "LineTraceSingleByChannel")
		int LineTraceRange = 1000000;	// 10 km -> 1000000 cm

	// Start the tank moving the barrel so that a shot would hit the target intersecting with the cross hair
	void AimTowardsCrossHair();

	// Return an OUT parameter, true if hit the landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};