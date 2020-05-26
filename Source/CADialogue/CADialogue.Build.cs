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

                "CADialogueDebug",
            }
			);

        bFasterWithoutUnity = true;
        bEnforceIWYU = true;
    }
}
