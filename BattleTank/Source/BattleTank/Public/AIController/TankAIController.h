// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pawn/Tank.h"
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

	ATankAIController();
	virtual ~ATankAIController();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
};
