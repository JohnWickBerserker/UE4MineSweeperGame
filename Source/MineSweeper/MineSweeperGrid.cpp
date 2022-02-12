// Author: Elkin Sergei

#include "MineSweeperGrid.h"
#include "MineSweeperTile.h"

AMineSweeperGrid::AMineSweeperGrid()
{
	NumRows = 5;
	NumColumns = 5;
	BlockSize = 128.f;
	NumMines = 0;
	NumChecked = 0;
	_isGameFinished = false;
	_isGameWon = false;
}

void AMineSweeperGrid::BeginPlay()
{
	Super::BeginPlay();

	SetSize(NumRows, NumColumns, BlockSize);
	BeginGame(NumRows * NumColumns / 5);
}

void AMineSweeperGrid::DestroyBlocks()
{
	// remove later, Blocks.Empty() does this
	for (AMineSweeperTile* block : Blocks)
	{
		block->Destroy();
	}

	Blocks.Empty();
}

void AMineSweeperGrid::ResetBlocks()
{
	for (AMineSweeperTile* block : Blocks)
	{
		block->IsChecked = false;
		block->IsMined = false;
		block->MinesNearCount = 0;
		block->SetMaterial(HiddenMaterial);
	}
}

void AMineSweeperGrid::PlaceMine(AMineSweeperTile* block)
{
	block->IsMined = true;
	int32 dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	int32 dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	for (int32 i = 0; i < 8; i++)
	{
		int32 r = block->Row + dr[i];
		int32 c = block->Column + dc[i];
		if (r >= 0 && c >= 0 && r < NumRows && c < NumColumns)
		{
			AMineSweeperTile* nearBlock = Blocks[r * NumColumns + c];
			nearBlock->MinesNearCount++;
		}
	}
}

void AMineSweeperGrid::UpdateBlockVisual(AMineSweeperTile* block)
{
	if (!block->IsChecked)
	{
		block->SetMaterial(HiddenMaterial);
		return;
	}
	if (block->IsMined)
	{
		block->SetMaterial(MineMaterial);
		return;
	}
	if (block->MinesNearCount < DigitMaterials.Num())
	{
		block->SetMaterial(DigitMaterials[block->MinesNearCount]);
	}
	else
	{
		block->SetMaterial(HiddenMaterial);
	}
}

void AMineSweeperGrid::OnBlockClicked(AMineSweeperTile* block)
{
	if (_isGameFinished)
	{
		return;
	}
	if (block->IsChecked)
	{
		return;
	}
	block->IsChecked = true;
	NumChecked++;
	UpdateBlockVisual(block);
	if (block->IsMined)
	{
		_isGameFinished = true;
		_isGameWon = false;
		OnLose(block);
		return;
	}
	TArray<AMineSweeperTile*> zeroBlocks;
	if (block->MinesNearCount == 0)
	{
		zeroBlocks.Add(block);
	}
	int32 dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	int32 dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	while (zeroBlocks.Num() > 0)
	{
		AMineSweeperTile* zeroBlock = zeroBlocks.Last();
		zeroBlocks.RemoveAtSwap(zeroBlocks.Num()-1);
		for (int32 i = 0; i < 8; i++)
		{
			int32 r = zeroBlock->Row + dr[i];
			int32 c = zeroBlock->Column + dc[i];
			if (r >= 0 && c >= 0 && r < NumRows && c < NumColumns)
			{
				AMineSweeperTile* nearBlock = Blocks[r*NumColumns+c];
				if (!nearBlock->IsChecked)
				{
					nearBlock->IsChecked = true;
					NumChecked++;
					UpdateBlockVisual(nearBlock);
					if (nearBlock->MinesNearCount == 0)
					{
						zeroBlocks.Add(nearBlock);
					}
				}
			}
		}
	}
	const int32 numBlocks = NumRows * NumColumns;
	if (NumChecked + NumMines == numBlocks)
	{
		_isGameFinished = true;
		_isGameWon = true;
		OnWin(block);
	}
}

void AMineSweeperGrid::SetSize(int32 numOfRows, int32 numOfColumns, float blockSize)
{
	DestroyBlocks();

	NumRows = numOfRows;
	NumColumns = numOfColumns;
	BlockSize = blockSize;
	NumMines = 0;
	NumChecked = 0;
	_isGameFinished = false;
	_isGameWon = false;

	FVector center = GetActorLocation();

	const int32 numBlocks = NumRows * NumColumns;

	for (int32 blockIndex = 0; blockIndex < numBlocks; blockIndex++)
	{
		float xOffset = (blockIndex % NumColumns) * BlockSize;
		float zOffset = (blockIndex / NumColumns) * BlockSize;
		xOffset = xOffset - (NumColumns - 1) * BlockSize / 2.f;
		zOffset = (NumRows - 1) * BlockSize / 2.f - zOffset;

		const FVector blockLocation = FVector(xOffset, 0.f, zOffset) + GetActorLocation();

		AMineSweeperTile* newBlock = GetWorld()->SpawnActor<AMineSweeperTile>(BlockClass, blockLocation, FRotator(0, 0, 0));

		if (newBlock != nullptr)
		{
			float scale = BlockSize / 128.f;
			newBlock->SetActorScale3D(FVector(scale, scale, scale));
			newBlock->OwningGrid = this;
			newBlock->Row = blockIndex / NumColumns;
			newBlock->Column = blockIndex % NumColumns;
			newBlock->SetMaterial(HiddenMaterial);
			Blocks.Add(newBlock);
		}
	}
}

void AMineSweeperGrid::BeginGame(int32 numMines)
{
	const int32 numBlocks = NumRows * NumColumns;
	if (numMines > numBlocks)
	{
		numMines = numBlocks;
	}

	NumMines = numMines;
	NumChecked = 0;
	_isGameFinished = false;
	_isGameWon = false;

	ResetBlocks();

	TArray<AMineSweeperTile*> freeBlocks;
	for (AMineSweeperTile* block : Blocks)
	{
		freeBlocks.Add(block);
	}

	while (numMines > 0)
	{
		int32 blockIndex = FMath::RandHelper(freeBlocks.Num());
		AMineSweeperTile* block = freeBlocks[blockIndex];
		freeBlocks.RemoveAtSwap(blockIndex);
		PlaceMine(block);
		numMines--;
	}
}
