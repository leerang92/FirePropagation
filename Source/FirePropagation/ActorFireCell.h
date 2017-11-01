// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "ActorFireCell.generated.h"

UCLASS()
class FIREPROPAGATION_API AActorFireCell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorFireCell();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCol;

	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystem* FireFX;

	UPROPERTY()
	UParticleSystemComponent* FireFXComp;

	UFUNCTION()
	UParticleSystemComponent* PlayParticle(UParticleSystem* Particle);

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void SetupCell();

	UPROPERTY(EditAnywhere, Category = "Fire Information")
	float HP;

	UPROPERTY(EditAnywhere, Category = "Fire Information")
	float Slop;

	FORCEINLINE bool GetIsFire() const { return IsFire; }

private:
	bool IsFire : 1;
};
