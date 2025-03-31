using UnrealBuildTool;
using System.IO;

public class QuestEditor : ModuleRules
{
    public QuestEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;


        //PublicIncludePaths.AddRange(new string[] { "QuestEditor/Public" });
        PrivateIncludePaths.AddRange(new string[] { "QuestEditor/Private" });

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core", "CoreUObject", "Engine", "Slate", "SlateCore", "EditorStyle", "UnrealEd","PropertyEditor","QuestEditorRuntime"
        });

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "ToolMenus" });
        }


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "AssetTools",
                "UnrealEd",
                "PropertyEditor",
                "Projects",
                "GraphEditor", 
                "QuestEditorRuntime",
                "KismetCompiler",
                "BlueprintGraph"
            }
        );
        
        
    }
}