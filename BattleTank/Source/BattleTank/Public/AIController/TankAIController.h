// Copyright TempleGames GmbH

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

protected:

	// How close can the AI tank get, in cm
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float AcceptancRadius = 8000;
};
