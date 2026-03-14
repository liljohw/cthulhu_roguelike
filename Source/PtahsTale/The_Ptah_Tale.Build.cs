using UnrealBuildTool;

public class The_Ptah_Tale : ModuleRules
{
    public The_Ptah_Tale(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "UMG",
            "Slate",
            "SlateCore",
            "AIModule",
            "NavigationSystem"
        });
    }
}
