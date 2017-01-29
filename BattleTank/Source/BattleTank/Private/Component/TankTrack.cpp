// Copyright TempleGames GmbH

#include "BattleTank.h"
#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto TankVelocity = GetOwner()->GetVelocity();
	auto TankRightDirection = GetOwner()->GetActorRightVector();

	// if the angle is 0 (both vectors facing right) the right speed will be the speed of the tank
	auto SlippageSpeed = FVector::DotProduct(TankVelocity, TankRightDirection);

	// Work-out the required acceleration this frame to correct
	auto CorrectionAcceleration = - (SlippageSpeed / DeltaTime * TankRightDirection);

	// Calculate and apply sideways for (F = m * a)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Divided by two because we have two tracks
	TankRoot->AddForce(CorrectionForce);
}

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

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Touching the ground!"), *GetName());
}
