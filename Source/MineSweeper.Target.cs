using UnrealBuildTool;
using System.Collections.Generic;

public class MineSweeperTarget : TargetRules
{
	public MineSweeperTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("MineSweeper");
	}
}
