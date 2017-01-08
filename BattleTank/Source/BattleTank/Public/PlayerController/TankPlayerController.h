// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pawn/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATankPlayerController();
	~ATankPlayerController();

	ATank* GetControlledTank() const;
	
	
};
