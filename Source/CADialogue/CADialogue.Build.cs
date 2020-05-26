// Some copyright should be here...

using UnrealBuildTool;

public class CADialogue : ModuleRules
{
	public CADialogue(ReadOnlyTargetRules Target) : base(Target)
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
