// Author: Elkin Sergei

#include "MineSweeperGameMode.h"
#include "MineSweeperPlayerController.h"

AMineSweeperGameMode::AMineSweeperGameMode()
{
	PlayerControllerClass = AMineSweeperPlayerController::StaticClass();
}
