// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "Weapon.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
	
}

void UWeaponComponent::SpawnWeapon() {
	if (!GetWorld()) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;

	CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass);
	if (!CurrentWeapon) return;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachName[SelectedAttributeIndex]);
	CurrentWeapon->SetOwner(Character);
}

void UWeaponComponent::StartFire()
{
	if (!CurrentWeapon) return;

	CurrentWeapon->StartFire(IsFire,IsShoot);
}

void UWeaponComponent::StopFire()
{
	if (CurrentWeapon) {
		CurrentWeapon->StopFire(IsFire, IsShoot);

	}
}

bool UWeaponComponent::IsFiring() const
{
	return IsFire;
}

bool UWeaponComponent::IsShooting() const
{
	return IsShoot;
}