// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SExplosiveBarrel.generated.h"

class USHealthComponent;
class UStaticMeshComponent;
class URadialForceComponent;
class UParticleSystem;
class UMaterialInterface;

UCLASS()
class COOPGAME_API ASExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplosiveBarrel();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USHealthComponent* OwningHealthComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* ForceComp;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	UParticleSystem* ExplodeEffect;

	UPROPERTY(ReplicatedUsing=OnRep_Exploded)
	bool bExploded;

	UFUNCTION()
	void OnHealthChanged(USHealthComponent* HealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void OnRep_Exploded();

	void ExplosionEffects();

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	UMaterialInterface* ExplodedBarrelMat;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	float ImpulseStrength;

public:	
	
	
};
