using UnrealBuildTool;
using System.Collections.Generic;

public class MineSweeperEditorTarget : TargetRules
{
	public MineSweeperEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("MineSweeper");
	}
}
