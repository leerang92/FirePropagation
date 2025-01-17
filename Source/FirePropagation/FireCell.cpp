// Fill out your copyright notice in the Description page of Project Settings.

#include "FireCell.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"




// Sets default values
AFireCell::AFireCell()
{
	PrimaryActorTick.bCanEverTick = true;

	HP = 100.0f;
	Slop = 5.0f;

	BoxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCol->OnComponentBeginOverlap.AddDynamic(this, &AFireCell::OnOverlapBegin);
	RootComponent = BoxCol;
}

// Called every frame
void AFireCell::Tick(float DeltaTime)
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

UParticleSystemComponent * AFireCell::PlayParticle(UParticleSystem * Particle)
{
	if (Particle)
	{
		UParticleSystemComponent* FXComp;
		FXComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation());
		return FXComp;
	}
	return nullptr;
}

void AFireCell::SetupCell()
{
	if (!IsFire)
	{
		IsFire = true;
		
		FireFXComp = PlayParticle(FireFX);

		if (FireActor != NULL)
		{
			UE_LOG(LogClass, Warning, TEXT("Fire Box"));
			FireActor->FireProComp->SetupCell(GetActorLocation());
		}
	}
}

void AFireCell::SetFireComponent(AActor * NewClass)
{
	this->BoxCol->SetHiddenInGame(false);
	
	//FireActor = NewClass;
}

void AFireCell::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		UE_LOG(LogClass, Warning, TEXT("Begin Overlap"));
		if (OtherComp->ComponentHasTag("Fire"))
		{
			UE_LOG(LogClass, Warning, TEXT("Fire Tag"));
		}
	}
}

