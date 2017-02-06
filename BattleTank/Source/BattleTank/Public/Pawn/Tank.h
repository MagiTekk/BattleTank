// Copyright TempleGames GmbH

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	
	// Called by the Engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Returns CurrentHealth as a percentage of starting health, between 0 and 1
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetHealthPercent() const;

	FTankDelegate OnDeath;

	virtual void PossessedBy(AController* NewController) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 AIStartingHealth = 100;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		int32 PlayerStartingHealth = 200;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
		int32 StartingHealth;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth;
};
