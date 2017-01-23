// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"





void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("UTankTrack::SetThrottle: %f"), Throttle);

	// TODO: clamp actual throttle value so player can't over-drive
}
