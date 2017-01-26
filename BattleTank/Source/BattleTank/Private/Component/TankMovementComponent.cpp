// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Component/TankTrack.h"
#include "TankMovementComponent.h"




void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call super since we are replacing the functionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto DotProductResult = FVector::DotProduct(TankForward, AIForwardIntention);

	IntendMoveForward(DotProductResult);

	UE_LOG(LogTemp, Warning, TEXT("RequestDirectMove::TankName: %s MoveVelocity: %s"), *GetOwner()->GetName(), *MoveVelocity.ToString());
}
