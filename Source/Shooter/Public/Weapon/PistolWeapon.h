// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Weapon/BP_Bullet.h"
#include "PistolWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API APistolWeapon : public AWeapon
{
	GENERATED_BODY()
public:
	APistolWeapon();
	virtual void StartFire(bool& IsFire, bool& IsShoot) override;
	virtual void StopFire(bool& IsFire, bool& IsShoot) override;

protected:
	virtual void MakeShot() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ABP_Bullet> BulletClass;
private:
	FTimerHandle ShotTimerHandle;
};
