// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/PistolWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


APistolWeapon::APistolWeapon() {
	WeaponSkeletal = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetRootComponent(WeaponSkeletal);
}

void APistolWeapon::StartFire(bool& IsFire, bool& IsShoot)
{
	MakeShot();
	IsFire = false;
	IsShoot = true;
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &APistolWeapon::MakeShot, TimeBetweenShots, true);
}

void APistolWeapon::StopFire(bool& IsFire, bool& IsShoot)
{
	IsFire = false;
	IsShoot = false;
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}


void APistolWeapon::MakeShot()
{
	if (!GetWorld()) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) false;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
	ABP_Bullet* Bullet = GetWorld()->SpawnActorDeferred<ABP_Bullet>(BulletClass, SpawnTransform);
	if (Bullet) {
		MakeDamage(HitResult);
		Bullet->SetShotDirection(Direction);
		Bullet->FinishSpawning(SpawnTransform);
	}
}