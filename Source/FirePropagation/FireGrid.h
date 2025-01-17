// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FireCell.h"
#include "Runtime/Core/Public/Containers/Queue.h"
#include "GameFramework/Actor.h"
#include "FireGrid.generated.h"

UCLASS()
class FIREPROPAGATION_API AFireGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireGrid();

public:	

	void CreateCell(FVector HitPoint);
	
	UPROPERTY(EditAnywhere, Category = "Fire Cell")
	TSubclassOf<AActor> CellActor;

	UPROPERTY()
	TArray<class AFireCell*> FireCells;

	// ���� �迭
	TArray<int32> Direct;

	TArray<int32> CellIndex;

	void SearchCell();

	int GetNextCellIndex(int index);

	UPROPERTY(EditAnywhere, Category = "Cell Information")
	float OffsetX;

	UPROPERTY(EditAnywhere, Category = "Cell Information")
	float OffsetY;

	UPROPERTY(EditAnywhere, Category = "Cell Information")
	float CellSize;

private:

	FTimerHandle CellTimer;

	void ActiveCell();
};
