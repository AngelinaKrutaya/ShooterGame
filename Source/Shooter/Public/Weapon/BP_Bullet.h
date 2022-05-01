// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BP_Bullet.generated.h"
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTER_API ABP_Bullet : public AActor
{
	GENERATED_BODY()
public:
	ABP_Bullet();
	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageRadius = 5.0f;

	virtual void BeginPlay() override;

private:
	FVector ShotDirection;
	UFUNCTION()
	void OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
