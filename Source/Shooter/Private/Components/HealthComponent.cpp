// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	OnHealthChanged.Broadcast(Health);
	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamageHandle);
	}
}


float UHealthComponent::GetHealth()
{
	return Health;
}

void UHealthComponent::OnTakeAnyDamageHandle(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);

	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (AutoHeal && GetWorld()) {
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle,this, &UHealthComponent::HealUpdate,HealUpdateTime, true, HealDelay);
	}
}

void UHealthComponent::HealUpdate() {
	Health = FMath::Min(Health + HealModifier, MaxHealth);
	OnHealthChanged.Broadcast(Health);

	if (Health == MaxHealth && GetWorld()) {
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}


