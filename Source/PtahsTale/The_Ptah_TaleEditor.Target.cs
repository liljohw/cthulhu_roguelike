using UnrealBuildTool;
using System.Collections.Generic;

public class The_Ptah_TaleEditorTarget : TargetRules
{
    public The_Ptah_TaleEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        ExtraModuleNames.Add("The_Ptah_Tale");
    }
}
