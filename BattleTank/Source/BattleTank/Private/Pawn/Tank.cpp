// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ATank::~ATank()
{

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATank::AimAt(FVector Hitlocation)
{
	FString OurTankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *OurTankName, *Hitlocation.ToString());
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* InputComponentParam)
{
	Super::SetupPlayerInputComponent(InputComponentParam);

}

