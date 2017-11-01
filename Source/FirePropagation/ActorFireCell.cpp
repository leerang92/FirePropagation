// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorFireCell.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AActorFireCell::AActorFireCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HP = 100.0f;
	Slop = 5.0f;

	BoxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = BoxCol;
}

// Called every frame
void AActorFireCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsFire)
	{
		HP -= DeltaTime * Slop;
		if (HP <= 0.0f && FireFXComp != nullptr)
		{
			FireFXComp->DeactivateSystem();
			IsFire = false;
			SetLifeSpan(0.1f);
		}
	}
}


UParticleSystemComponent * AActorFireCell::PlayParticle(UParticleSystem * Particle)
{
	if (Particle)
	{
		UParticleSystemComponent* FXComp;
		FXComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation());
		return FXComp;
	}
	return nullptr;
}

void AActorFireCell::SetupCell()
{
	if (!IsFire)
	{
		UE_LOG(LogClass, Warning, TEXT("Setup"));
		IsFire = true;
		FireFXComp = PlayParticle(FireFX);
	}
}
