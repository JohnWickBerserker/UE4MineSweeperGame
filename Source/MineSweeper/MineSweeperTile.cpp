// Author: Elkin Sergei

#include "MineSweeperTile.h"
#include "MineSweeperGrid.h"
#include "Materials/MaterialInstance.h"

AMineSweeperTile::AMineSweeperTile()
{
	IsMined = false;
	IsChecked = false;
	MinesNearCount = 0;

	OnClicked.AddUniqueDynamic(this, &AMineSweeperTile::BlockClicked);
	OnInputTouchBegin.AddUniqueDynamic(this, &AMineSweeperTile::OnFingerPressedBlock);
}

void AMineSweeperTile::BlockClicked(AActor* actor, FKey buttonClicked)
{
	HandleClicked();
}


void AMineSweeperTile::OnFingerPressedBlock(ETouchIndex::Type fingerIndex, AActor* actor)
{
	HandleClicked();
}

void AMineSweeperTile::HandleClicked()
{
	OwningGrid->OnBlockClicked(this);
}

void AMineSweeperTile::SetMaterial(UMaterialInstance* materialInstance)
{
	this->GetRenderComponent()->SetMaterial(0, materialInstance);
}
