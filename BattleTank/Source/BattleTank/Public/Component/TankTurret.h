// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), hidecategories=("Collision") )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankTurret();

	void RotateTurret(float RelativeSpeed);

private:

	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxDegreesPerSecond = 5.f;
		
	
};
