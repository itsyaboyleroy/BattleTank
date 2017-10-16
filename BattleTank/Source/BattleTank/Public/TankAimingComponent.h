// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "TankAimingComponent.generated.h"

UENUM() 
enum class EFiringState : uint8
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
	EFiringState FiringState;

public:	
	void AimAt(FVector OutHitLocation);

	UFUNCTION(BluePrintCallable, Category = input)
	void Fire();

	virtual void BeginPlay() override;

	UFUNCTION(BluePrintCallable, Category = Setup)
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	EFiringState GetFiringState() const;
	
	UFUNCTION(BluePrintCallable, Category = Firing)
	int GetRoundsLeft() const;

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

	bool IsBarrelMoving();

	UPROPERTY(EditAnywhere, Category = Firing)
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditAnywhere, Category = Firing)
	float TimeInbetweenShotsInSeconds = .5;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	FVector AimDirection;

	int RoundsLeft = 4;

	double OutOfAmmoTime;
};
