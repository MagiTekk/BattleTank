// Copyright TempleGames GmbH

#include "BattleTank.h"
#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	FMath::Clamp<float>(Throttle, -1.0f, 1.0f);

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	// Apply the force to the Tank itself, We chose the cast the USceneComponent to UPrimitiveComponent
	// because it is the first class under USceneComponent that allows me to add a force
	// I want to use the simplest class possible
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
