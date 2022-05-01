// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/SwordWeapon.h"
#include "Weapon/Raw.h"

void ASwordWeapon::StopFire(bool& IsFire, bool& IsShoot)
{
	IsFire = false;
	IsShoot = false;
}

ASwordWeapon::ASwordWeapon() {
	WeaponSkeletal = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetRootComponent(WeaponSkeletal);

}

void ASwordWeapon::StartFire(bool& IsFire, bool& IsShoot)
{
	IsFire = false;
	IsShoot = true;
	MakeShot();
}

void ASwordWeapon::MakeShot()
{
	if (!GetWorld()) return;

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) false;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();
	
	const FTransform SpawnTransform(FRotator::ZeroRotator,GetMuzzleWorldLocation());
	ARaw* Arrow = GetWorld()->SpawnActorDeferred<ARaw>(ArrowClass , SpawnTransform);
	if (Arrow) {
		Arrow->SetShotDirection(Direction);
		Arrow->FinishSpawning(SpawnTransform);
	}
}
