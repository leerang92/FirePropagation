// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "FireActor.h"
#include "FireCell.generated.h"

UCLASS()
class FIREPROPAGATION_API AFireCell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireCell();

public:	
	// Called every frame
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

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void SetFireComponent(AActor* NewClass);

	UPROPERTY(BlueprintReadWrite)
	class AFireActor* FireActor;

private:
	bool IsFire : 1;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
