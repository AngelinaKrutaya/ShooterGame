// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "MyCharacter.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Math/Vector.h"
#include "Engine/EngineTypes.h"

// Sets default values
DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	//check(WeaponMesh);
}


bool AWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const {
	const auto Controller = GetPlayerController();
	if (!Controller) return false;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	return true;
}

APlayerController* AWeapon::GetPlayerController() const {
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return nullptr;

	return Player->GetController<APlayerController>();
}

FVector AWeapon::GetWeaponWorldLocation() const
{
	return WeaponMesh->GetSocketLocation("MuzzleSocket");
}

FVector AWeapon::GetMuzzleWorldLocation() const
{
	return WeaponSkeletal->GetSocketLocation("MuzzleSocket");
}

bool AWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const {
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const FVector ShootDirection = ViewRotation.Vector();
	float Angle = FMath::Acos(FVector::DotProduct(TraceStart, ShootDirection));
	//if (Angle > 1.57 || Angle<0) return;
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
	return true;
}

void AWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) {
	if (!GetWorld()) return;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void AWeapon::MakeDamage(const FHitResult& HitResult) {
	const auto Actor = HitResult.GetActor();
	if (!Actor) return;

	Actor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}