// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Weapon.h"
#include "GunWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AGunWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	AGunWeapon();
	virtual void StartFire(bool& IsFire, bool& IsShoot) override;
	virtual void StopFire(bool& IsFire, bool& IsShoot) override;

protected:
	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
private:
	FTimerHandle ShotTimerHandle;
};
