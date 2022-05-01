// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/BP_Bullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ABP_Bullet::ABP_Bullet()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(5.0f);
	//CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);


	SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
}

void ABP_Bullet::BeginPlay()
{
	Super::BeginPlay();
	check(MovementComponent);
	//check(CollisionComponent);
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	//CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	//CollisionComponent->OnComponentHit.AddDynamic(this, &ABP_Bullet::OnBulletHit);
	SetLifeSpan(5.0f);
}

void ABP_Bullet::OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;
	MovementComponent->StopMovementImmediately();
	//make damage
	//UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), 
	//	DamageRadius, UDamageType::StaticClass(), {GetOwner()}, this, nullptr, false);
	//DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);
	//Destroy();

}


