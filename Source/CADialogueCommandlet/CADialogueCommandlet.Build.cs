// Some copyright should be here...

using UnrealBuildTool;

public class CADialogueCommandlet : ModuleRules
{
	public CADialogueCommandlet(ReadOnlyTargetRules Target) : base(Target)
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
