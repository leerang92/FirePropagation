// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorFireCell.h"
#include "FirePropagationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIREPROPAGATION_API UFirePropagationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFirePropagationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, Category = "Cell")
	bool IsCell;

	UPROPERTY(EditAnywhere, Category = "Cell")
	TSubclassOf<class AActor> CellActor;

	UFUNCTION(BlueprintCallable, Category = "Fire")
	FORCEINLINE bool GetIsCell() const { return IsCell; }

	UPROPERTY(EditAnywhere, Category = "Cell")
	float Row;
	
	UPROPERTY(EditAnywhere, Category = "Cell")
	float Coloume;

	UPROPERTY(EditAnywhere, Category = "Cell")
	float Floor;

	UPROPERTY(EditAnywhere, Category = "Cell")
	float CellSize;

	TArray<int32> Direct;

	TArray<int32> CellIndex;

	FTimerHandle CellTimer;

	void SetupCell(FVector CellLoc);

	void SearchCell();

	int GetNextCellIndex(int Index);

	void ActiveCell();

private:
	void CreateCell();

	TArray<class AActorFireCell*> CellArr;
};
