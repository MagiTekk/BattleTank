// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void AimAt(FVector& Hitlocation);

protected:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponentParam) override;

	UTankAimingComponent* TankAimingComponent = nullptr;

private:

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000;	// TODO find sensible default
	
};
