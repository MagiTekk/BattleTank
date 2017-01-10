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
	HitLocation = FVector(1.0);
	return true;
	/*FHitResult RV_Hit(ForceInit);
	SingleLineTrace(RV_Hit);

	if (RV_Hit.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("bBlockingHit: %s"), *RV_Hit.GetActor()->GetName());
		HitLocation = RV_Hit.Location;
		return true;
	}
	return false;*/
}

bool ATankPlayerController::SingleLineTrace(FHitResult &RV_Hit) const
{
	return true;

	/*FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;


	UCameraComponent* CameraComponent = Cast<UCameraComponent>(GetControlledTank()->GetComponentByClass(UCameraComponent::StaticClass()));
	//FVector Start = CameraComponent->GetComponentLocation() + CameraComponent->Bounds

	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + (FVector::ForwardVector * 10000);

	return GetWorld()->LineTraceSingleByChannel(
		RV_Hit,			//result
		Start,			//start
		End,			//end
		ECC_Visibility, //collision channel
		RV_TraceParams
		);
		*/
}
