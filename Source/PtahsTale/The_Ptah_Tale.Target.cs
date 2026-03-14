using UnrealBuildTool;
using System.Collections.Generic;

public class The_Ptah_TaleTarget : TargetRules
{
    public The_Ptah_TaleTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        ExtraModuleNames.Add("The_Ptah_Tale");
    }
}
