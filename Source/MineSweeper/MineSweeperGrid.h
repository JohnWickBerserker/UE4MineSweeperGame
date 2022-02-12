// Author: Elkin Sergei

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MineSweeperTile.h"
#include "MineSweeperGrid.generated.h"

UCLASS()
class MINESWEEPER_API AMineSweeperGrid : public AActor
{
	GENERATED_BODY()
	
public:
	AMineSweeperGrid();

	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 NumRows;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	int32 NumColumns;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSize;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	int32 NumMines;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	int32 NumChecked;

	UPROPERTY(Category = Grid, EditAnywhere)
	TSubclassOf<class AMineSweeperTile> BlockClass;

	UPROPERTY(Category = Grid, EditAnywhere)
	UMaterialInstance* MineMaterial;

	UPROPERTY(Category = Grid, EditAnywhere)
	class UMaterialInstance* HiddenMaterial;

	UPROPERTY(Category = Grid, EditAnywhere)
	TArray<UMaterialInstance*> DigitMaterials;

	UPROPERTY(Category = Grid, EditAnywhere, BlueprintReadOnly)
	TArray<AMineSweeperTile*> Blocks;

	void OnBlockClicked(AMineSweeperTile* block);

	UFUNCTION(BlueprintCallable, Category = "MineSweeper Game")
	void SetSize(int32 numOfRows, int32 numOfColumns, float sizeOfBlock);

	UFUNCTION(BlueprintCallable, Category = "MineSweeper Game")
	void BeginGame(int32 numOfMines);

	UFUNCTION(BlueprintCallable, Category = "MineSweeper Game")
	bool IsGameFinished() { return _isGameFinished; }

	UFUNCTION(BlueprintCallable, Category = "MineSweeper Game")
	bool IsGameWon() { return _isGameWon; }

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Events")
	void OnWin(AMineSweeperTile* block);

	UFUNCTION(BlueprintImplementableEvent, Category = "Game Events")
	void OnLose(AMineSweeperTile* block);

protected:
	virtual void BeginPlay() override;

	void DestroyBlocks();

	void ResetBlocks();

	void PlaceMine(AMineSweeperTile* block);

	void UpdateBlockVisual(AMineSweeperTile* block);

private:
	bool _isGameFinished;
	bool _isGameWon;
};
