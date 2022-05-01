// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Raw.generated.h"
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTER_API ARaw : public AActor
{
	GENERATED_BODY()
	
public:	
	ARaw();
	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;

	virtual void BeginPlay() override;

private:	
	FVector ShotDirection;
};
