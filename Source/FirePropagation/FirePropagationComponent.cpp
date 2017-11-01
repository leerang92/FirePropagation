// Fill out your copyright notice in the Description page of Project Settings.

#include "FirePropagationComponent.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UFirePropagationComponent::UFirePropagationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	IsCell = false;
	Row = 2.0f;
	Coloume = 2.0f;
	Floor = 2.0f;
	CellSize = 50.0f;

	// 인덱스의 주위 8방향
	Direct.Add(-Row - 1);
	Direct.Add(-Row);
	Direct.Add(-Row + 1);
	Direct.Add(1);
	Direct.Add(Row + 1);
	Direct.Add(Row);
	Direct.Add(Row - 1);
	Direct.Add(-1);
}


// Called when the game starts
void UFirePropagationComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CreateCell();
	
}


// Called every frame
void UFirePropagationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFirePropagationComponent::SetupCell(FVector CellLoc)
{
	UE_LOG(LogClass, Warning, TEXT("CELL"));
	CellArr[0]->SetupCell();
	CellIndex.Add(0);
	SearchCell();
}

void UFirePropagationComponent::SearchCell()
{
	TArray<int32> TempArr;
	int CurrentIndex = 0;
	for (int j = 0; j < CellIndex.Num(); ++j)
	{
		CurrentIndex = CellIndex[j];
		CellIndex.RemoveAt(j);
		for (int i = 0; i < Direct.Num(); ++i)
		{
			// 주위 쉘 인덱스 찾기
			int NextIndex = GetNextCellIndex(CurrentIndex + Direct[i]);
			if (NextIndex > 0)
			{
				TempArr.Add(NextIndex);
			}
		}
	}
	CellIndex = TempArr;

	// 일정 시간 후 활성화 함수 호출
	GetWorld()->GetTimerManager().SetTimer(CellTimer, this, &UFirePropagationComponent::ActiveCell, 3.0f, false);
}

int UFirePropagationComponent::GetNextCellIndex(int Index)
{
	if (Index >= 0 && Index < CellArr.Num() && !CellArr[Index]->GetIsFire())
	{
		return Index;
	}
	return -1;
}

void UFirePropagationComponent::ActiveCell()
{

	for (int i = 0; i < CellIndex.Num(); ++i)
	{
		CellArr[CellIndex[i]]->SetupCell();
	}
	GetWorld()->GetTimerManager().ClearTimer(CellTimer);
	SearchCell();
}

void UFirePropagationComponent::CreateCell()
{
	float Widgt = (static_cast<int>(Row) % 2 == 0) ? (Row * 0.5f) * CellSize : ((Row - 1) * 0.5f) * CellSize;
	float Height = (static_cast<int>(Coloume) % 2 == 0) ? (Coloume * 0.5f) * CellSize : ((Coloume - 1) * 0.5f) * CellSize;

	const FVector ActorLoc = GetOwner()->GetActorLocation();

	for (int f = 0; f < Floor; ++f)
	{
		for (int i = 0; i < Row; ++i)
		{
			for (int j = 0; j < Coloume; ++j)
			{
				const FVector SpawnLoc = FVector(
					(ActorLoc.X - Widgt) + (i * CellSize),
					(ActorLoc.Y - Height) + (j * CellSize),
					ActorLoc.Z + (f * CellSize));

				AActorFireCell* NewCell = GetWorld()->SpawnActor<AActorFireCell>(CellActor, SpawnLoc, FRotator::ZeroRotator);
				check(NewCell);
				NewCell->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
				CellArr.Add(NewCell);
			}
		}
	}
}

