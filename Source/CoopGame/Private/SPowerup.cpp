// Fill out your copyright notice in the Description page of Project Settings.

#include "SPowerup.h"
#include "TimerManager.h"


// Sets default values
ASPowerup::ASPowerup()
{
	PowerupInterval = 0.0f;
	TotalNrOfTicks = 0;
}

// Called when the game starts or when spawned
void ASPowerup::BeginPlay()
{
	Super::BeginPlay();
	
	
	
}

void ASPowerup::OnTickPowerup()
{
	TicksProcessed++;

	if (TicksProcessed >= TotalNrOfTicks)
	{
		OnExpired();

		GetWorldTimerManager().ClearTimer(TimerHandle_PowerupTick);
	}

}

void ASPowerup::ActivatePowerup()
{
	if (PowerupInterval >= 0.0f)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_PowerupTick, this, &ASPowerup::OnTickPowerup, PowerupInterval, true, 0.0f);
	}
	else
	{
		OnTickPowerup();
	}
}

