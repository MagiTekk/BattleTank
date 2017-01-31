// Copyright TempleGames GmbH

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Input")
		void Fire();

	UFUNCTION(BlueprintCallable, Category = "Ammo")
		int GetAmmo() const;

	EFiringStatus GetFiringStatus() const;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Reloading")
		EFiringStatus FiringStatus = EFiringStatus::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
		int Ammo = 5;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	bool IsBarrelMoving();
	void MoveBarrelTowards();
	void MoveTurretTowards();

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	FVector AimDirection = FVector(0);

	double LastFireTime = 0;

};
