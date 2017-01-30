// Copyright TempleGames GmbH

#include "BattleTank.h"
#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce()
{
	auto TankVelocity = GetOwner()->GetVelocity();
	auto TankRightDirection = GetOwner()->GetActorRightVector();

	// if the angle is 0 (both vectors facing right) the right speed will be the speed of the tank
	auto SlippageSpeed = FVector::DotProduct(TankVelocity, TankRightDirection);

	// Work-out the required acceleration this frame to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime * TankRightDirection);

	// Calculate and apply sideways for (F = m * a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Divided by two because we have two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	// Apply the force to the Tank itself, We chose the cast the USceneComponent to UPrimitiveComponent
	// because it is the first class under USceneComponent that allows me to add a force
	// I want to use the simplest class possible
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

// OnHit gets called every frame, with this we are making sure the tanks can only move when they are touching the ground
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	ApplySidewaysForce();

	// Reset the throttle to avoid neverending movement
	CurrentThrottle = 0;
}
