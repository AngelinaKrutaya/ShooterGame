// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/GunWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
AGunWeapon::AGunWeapon() {
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
}
void AGunWeapon::StartFire(bool& IsFire, bool& IsShoot)
{
	MakeShot();
	IsFire = true;
	IsShoot = false;
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AGunWeapon::MakeShot, TimeBetweenShots, true);
}

void AGunWeapon::StopFire(bool& IsFire, bool& IsShoot)
{
	IsFire = false;
	IsShoot = false;
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}


void AGunWeapon::MakeShot()
{
	if (!GetWorld()) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) false;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit) {
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(), GetWeaponWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);

	}
	else {
		DrawDebugLine(GetWorld(), GetWeaponWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
}

bool AGunWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	float Angle = FMath::Acos(FVector::DotProduct(TraceStart, ShootDirection));
	//if (Angle > 1.57 || Angle<0) return;
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}
