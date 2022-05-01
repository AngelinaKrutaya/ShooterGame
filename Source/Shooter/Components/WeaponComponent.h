// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AWeapon;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UWeaponComponent();
	void StartFire();
	void StopFire();

	UFUNCTION(BlueprintCallable)
	bool IsFiring() const;

	UFUNCTION(BlueprintCallable)
	bool IsShooting() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AWeapon> WeaponClass;

	//UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	//FName WeaponAttachName = "WeaponSocket";

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	TArray<FName> WeaponAttachName = { "WeaponSocket" ,"PistolSocket"};

	UPROPERTY(EditDefaultsOnly, meta = (ArrayClamp = "Weapon"))
	int32 SelectedAttributeIndex = 0;
private:	
	UPROPERTY()
	AWeapon* CurrentWeapon = nullptr;
	void SpawnWeapon();
	bool IsFire = false;
	bool IsShoot = false;
};
