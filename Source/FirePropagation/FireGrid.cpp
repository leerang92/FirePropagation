// Fill out your copyright notice in the Description page of Project Settings.

#include "FireGrid.h"
#include "Engine/World.h"


// Sets default values
AFireGrid::AFireGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OffsetX = 11.0f;
	OffsetY = 11.0f;
	CellSize = 70.0f;

	// 인덱스의 주위 8방향
	Direct.Add(-OffsetX - 1);
	Direct.Add(-OffsetX);
	Direct.Add(-OffsetX + 1);
	Direct.Add(1);
	Direct.Add(OffsetX + 1);
	Direct.Add(OffsetX);
	Direct.Add(OffsetX - 1);
	Direct.Add(-1);

}

// Called when the game starts or when spawned
void AFireGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFireGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFireGrid::CreateCell(FVector HitPoint)
{
	const FVector ActorLoc = GetActorLocation();

	float Widgt = (static_cast<int>(OffsetX) % 2 == 0) ? (OffsetX / 2.0f) * CellSize : ((OffsetX - 1) / 2.0f) * CellSize;
	float Hegiht = (static_cast<int>(OffsetY) % 2 == 0) ? (OffsetY / 2.0f) * CellSize : ((OffsetY - 1) / 2.0f) * CellSize;
	 
	// 2차원 행렬 생성
	int StartIndex = 0;
	for (int x = 0; x < OffsetX; ++x)
	{
		for (int y = 0; y < OffsetY; ++y)
		{
			// 생성 위치 설정 및 생성
			const FVector SpawnLoc = FVector((ActorLoc.X - Widgt) + (x * CellSize),
											(ActorLoc.Y - Hegiht) + (y * CellSize), 
											ActorLoc.Z);
			AActor* Cell = GetWorld()->SpawnActor<AActor>(CellActor, SpawnLoc, FRotator::ZeroRotator);
			Cell->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);

			// FireCell로 형변환 후 배열에 저장
			AFireCell* FC = Cast<AFireCell>(Cell);
			check(FC);
			FireCells.Add(FC);

			// 시작 위치 찾기
			float Dist = FVector::Distance(HitPoint, SpawnLoc);
			if (Dist < 2.0f)
			{
				StartIndex = FireCells.Num() - 1;
			}
		}
	}
	FireCells[StartIndex]->SetupCell();
	CellIndex.Add(StartIndex);
	SearchCell();
}

void AFireGrid::SearchCell()
{
	TArray<int32> TempArr;
	int CurrentIndex = 0;
	for(int j = 0; j < CellIndex.Num(); ++j)
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
	GetWorld()->GetTimerManager().SetTimer(CellTimer, this, &AFireGrid::ActiveCell, 5.0f, false);
}

int AFireGrid::GetNextCellIndex(int index)
{
	if (index >= 0 && index < FireCells.Num() && !FireCells[index]->GetIsFire())
	{
		return index;
	}
	return -1;
}

void AFireGrid::ActiveCell()
{
	if (CellIndex.Num() <= 0)
	{
		SetLifeSpan(0.1f);
	}

	for (int i = 0; i < CellIndex.Num(); ++i)
	{
		FireCells[CellIndex[i]]->SetupCell();
	}
	GetWorld()->GetTimerManager().ClearTimer(CellTimer);
	SearchCell();
}

void AFireGrid::DestroyCell()
{

	
}

