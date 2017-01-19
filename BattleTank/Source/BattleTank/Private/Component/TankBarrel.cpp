// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"




UTankBarrel::UTankBarrel()
{

}

void UTankBarrel::Elevate(float DegreesPerSecond)
{
	// Move the barrel the right amount this frame
	// Given a may elevation speed, and the frame time
	UE_LOG(LogTemp, Warning, TEXT("UTankBarrel::Elevate called at speed %f "), DegreesPerSecond);
}
