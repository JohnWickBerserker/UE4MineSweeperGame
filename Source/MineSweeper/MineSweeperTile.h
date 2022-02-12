// Author: Elkin Sergei

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "PaperSpriteComponent.h"
#include "MineSweeperTile.generated.h"

UCLASS()
class MINESWEEPER_API AMineSweeperTile : public APaperSpriteActor
{
	GENERATED_BODY()

public:
	AMineSweeperTile();

	UPROPERTY()
	class AMineSweeperGrid* OwningGrid;

	UPROPERTY(BlueprintReadOnly)
	bool IsMined;

	UPROPERTY(BlueprintReadOnly)
	bool IsChecked;

	UPROPERTY(BlueprintReadOnly)
	int32 MinesNearCount;

	UPROPERTY(BlueprintReadOnly)
	int32 Row;

	UPROPERTY(BlueprintReadOnly)
	int32 Column;

	UFUNCTION()
	void BlockClicked(AActor* actor, FKey buttonClicked);

	UFUNCTION()
	void OnFingerPressedBlock(ETouchIndex::Type fingerIndex, AActor* actor);

	void HandleClicked();

	void SetMaterial(UMaterialInstance* materialInstance);
};
