// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be last include

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	void AimTowardsCrosshair(); // Start tank moving barrel for crosshair

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = .333333f;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = .5f;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector& LookDirection, FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

	UFUNCTION()
	void OnPossessedTankDeath();

	virtual void SetPawn(APawn* InPawn) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

};
