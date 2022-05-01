// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Weapon.h"
#include "SwordWeapon.generated.h"
class ARaw;
/**
 * 
 */
UCLASS()
class SHOOTER_API ASwordWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire(bool& IsFire, bool& IsShoot) override;
	virtual void StopFire(bool& IsFire, bool& IsShoot) override;
	ASwordWeapon();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ARaw> ArrowClass;

	virtual void MakeShot() override;
};
