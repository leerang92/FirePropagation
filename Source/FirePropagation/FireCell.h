// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "FireCell.generated.h"

UCLASS()
class FIREPROPAGATION_API AFireCell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireCell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCol;

	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystem* FireFX;

	UPROPERTY()
	UParticleSystemComponent* FireComp;

	UFUNCTION()
	UParticleSystemComponent* PlayParticle(UParticleSystem* Particle);

	void SetupCell();

	UPROPERTY(EditAnywhere, Category = "Fire Information")
	float HP;

	UPROPERTY(EditAnywhere, Category = "Fire Information")
	float Slop;

	FORCEINLINE bool GetIsFire() const { return IsFire; }

private:
	bool IsFire : 1;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
