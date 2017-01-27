// Copyright TempleGames GmbH

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	ATankAIController();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:

	// How close can the AI tank get
	float AcceptancRadius = 3000;
};
