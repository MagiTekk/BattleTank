// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Component/TankBarrel.h"
#include "Component/TankAimingComponent.h"
#include "Component/TankTurret.h"
#include "Projectile/Projectile.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	if (!Barrel) { return; }

	UE_LOG(LogTemp, Warning, TEXT("FIRE!!"));

	// Spawn a projectile from the barrel socket of the component
	const UStaticMeshSocket* Projectile_Socket = Barrel->GetSocketByName(FName("Projectile"));
	
	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint->GetOwnerClass(), Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATank::AimAt(FVector& Hitlocation)
{
	TankAimingComponent->AimAt(Hitlocation, LaunchSpeed);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* InputComponentParam)
{
	Super::SetupPlayerInputComponent(InputComponentParam);

}

