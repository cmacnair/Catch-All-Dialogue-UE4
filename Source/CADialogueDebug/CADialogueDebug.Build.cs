// Some copyright should be here...

using UnrealBuildTool;

public class CADialogueDebug : ModuleRules
{
	public CADialogueDebug(ReadOnlyTargetRules Target) : base(Target)
	{
        PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "Core",
                "CoreUObject",
				"Engine",
                "GameplayTags",
			}
			);

        bFasterWithoutUnity = true;
        bEnforceIWYU = true;
    }
}
