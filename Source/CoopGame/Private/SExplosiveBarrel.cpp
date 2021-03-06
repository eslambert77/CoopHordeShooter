// Fill out your copyright notice in the Description page of Project Settings.

#include "SExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "SHealthComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"



// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
	OwningHealthComp = CreateDefaultSubobject<USHealthComponent>(TEXT("HealthComp"));
	OwningHealthComp->OnHealthChanged.AddDynamic(this, &ASExplosiveBarrel::OnHealthChanged);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionObjectType(ECC_PhysicsBody);
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("ForceComp"));
	ForceComp->SetupAttachment(MeshComp);
	ForceComp->Radius = 250;
	ForceComp->bImpulseVelChange = true;
	ForceComp->bAutoActivate = false;
	ForceComp->bIgnoreOwningActor = true;

	bExploded = false;
	ImpulseStrength = 400;

	SetReplicates(true);
	SetReplicateMovement(true);

}

void ASExplosiveBarrel::OnHealthChanged(USHealthComponent* HealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Health <= 0.0f && !bExploded)
	{
		bExploded = true;

		ExplosionEffects();

		FVector ImpulseDirection = GetActorLocation().UpVector;
		MeshComp->AddImpulse(ImpulseDirection * ImpulseStrength, NAME_None, true);
		
		ForceComp->FireImpulse();
	}
}

void ASExplosiveBarrel::OnRep_Exploded()
{
	ExplosionEffects();
}

void ASExplosiveBarrel::ExplosionEffects()
{
	if (ExplodedBarrelMat) {
		MeshComp->SetMaterial(0, ExplodedBarrelMat);
	}

	if (ExplodeEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplodeEffect, GetActorLocation());
	}
}

void ASExplosiveBarrel::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASExplosiveBarrel, bExploded);

}

