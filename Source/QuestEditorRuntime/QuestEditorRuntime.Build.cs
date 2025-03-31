using UnrealBuildTool;
using System.IO;

public class QuestEditorRuntime : ModuleRules
{
    public QuestEditorRuntime(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "CoreUObject","Engine"
            }
        );

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd","ToolMenus" });
        }

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Slate",
                "SlateCore",
                "AssetRegistry",
            }
        );
        
        PublicDefinitions.Remove("WITH_MY_EDITOR=1");
        PublicDefinitions.Remove("WITH_MY_EDITOR=0");
        PublicDefinitions.Add("WITH_MY_EDITOR=1");
        
        /*if (Target.Type == TargetRules.TargetType.Editor)
        {
            PublicDefinitions.Remove("WITH_MY_EDITOR=0");
            PublicDefinitions.Add("WITH_MY_EDITOR=1");
            
        }
        else
        {
            PublicDefinitions.Remove("WITH_MY_EDITOR=1");
            PublicDefinitions.Add("WITH_MY_EDITOR=0");
        }*/
    }
}