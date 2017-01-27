// Copyright TempleGames GmbH

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class AProjectile;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector Hitlocation);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void Fire();

	UFUNCTION(BlueprintCallable, Category = "Component")
		UTankAimingComponent* GetTankAimingComponent() const;


	virtual void BeginPlay() override;

protected:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponentParam) override;
	
};
