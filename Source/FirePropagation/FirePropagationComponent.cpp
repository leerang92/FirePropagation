// Fill out your copyright notice in the Description page of Project Settings.

#include "FirePropagationComponent.h"


// Sets default values for this component's properties
UFirePropagationComponent::UFirePropagationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFirePropagationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFirePropagationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFirePropagationComponent::CreateCell()
{
	IsCell = true;
	FVector Scale = GetOwner()->GetActorScale3D();

	UE_LOG(LogClass, Warning, TEXT("%s"), *Scale.ToString());
}

