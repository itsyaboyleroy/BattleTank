// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "TankAimingComponent.generated.h"

UENUM() 
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringState = EFiringStatus::Reloading;

public:	
	void AimAt(FVector OutHitLocation);

	UFUNCTION(BluePrintCallable, Category = input)
	void Fire();

	UFUNCTION(BluePrintCallable, Category = Setup)
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

private:
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	UTankAimingComponent();

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000.0f;

	void MoveBarrelTowards(FVector AimDirection);

	void RotateTurretTowards(FVector AimDirection);

	double LastFireTime = 0;

	UPROPERTY(EditAnywhere, Category = Firing)
	float ReloadTimeInSeconds = 3;


};
