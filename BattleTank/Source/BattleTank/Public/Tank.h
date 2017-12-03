// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:

public:
	void AimAt(FVector OutHitLocation);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

private:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
		int32 CurrentHealth;

};
