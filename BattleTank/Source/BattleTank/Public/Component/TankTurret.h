// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
* TankTurret is just the class used to move around the barrel and Aim at the world
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))//, hidecategories=("Collision") )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankTurret();

	void Rotate(float RelativeSpeed);

private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegreesPerSecond = 25.f;
		
	
};
