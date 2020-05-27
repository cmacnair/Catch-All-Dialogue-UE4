#include "CADialogueCommandlet.h"
#include <AssetRegistryModule.h>
#include "CADialogueInstanceComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogCADialogue, Log, All);

int32 UCADialogueCommandlet::Main(const FString& FullCommandLine)
{
	UE_LOG(LogCADialogue, Log, TEXT("--------------------------------------------------------------------------------------------"));
	UE_LOG(LogCADialogue, Log, TEXT("Running CADialogue Commandlet"));
	TArray<FString> Tokens;
	TArray<FString> Switches;
	TMap<FString, FString> Params;
	ParseCommandLine(*FullCommandLine, Tokens, Switches, Params);

	// Right now, just implement the usage report feature
	PerformUsageReport();

	UE_LOG(LogCADialogue, Log, TEXT("Successfully finished running CADialogue Usage Report Commandlet"));
	UE_LOG(LogCADialogue, Log, TEXT("--------------------------------------------------------------------------------------------"));
	return 0;
}

bool UCADialogueCommandlet::PerformUsageReport()
{
	// Get a list of all sounds in use
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(AssetRegistryConstants::ModuleName);

	TArray<FAssetData> AssetDataList;
	AssetRegistryModule.Get().GetAssetsByClass(UCADialogueInstanceComponent::StaticClass()->GetFName(), AssetDataList);
	if (!AssetDataList.Num())
		return true;


	TMap<USoundBase*, FGameplayTagContainer> SoundsToInstancesMap;

	for (auto& DialogueInstanceComponentAsset : AssetDataList)
	{
		UCADialogueInstanceComponent* DialogueInstance = Cast<UCADialogueInstanceComponent>(DialogueInstanceComponentAsset.FastGetAsset());
		ensure(DialogueInstance);
		const TArray<class USoundBase*> SoundsInInstance = DialogueInstance->GetListOfAllSounds();

		for (auto& InstanceSoundIter : SoundsInInstance)
		{
			if (SoundsToInstancesMap.Contains(InstanceSoundIter))
			{
				if (!SoundsToInstancesMap[InstanceSoundIter].HasTag(DialogueInstance->InstanceTag))
				{
					SoundsToInstancesMap[InstanceSoundIter].AddTag(DialogueInstance->InstanceTag);
				}
			}
		}
	}

	for (auto& SoundsInInstancesIter : SoundsToInstancesMap)
	{
		UE_LOG(LogCADialogue, Log, TEXT("Sound Asset: %s Found in instances: %s"), *SoundsInInstancesIter.Key->GetName(), *SoundsInInstancesIter.Value.ToString());
	}
	

	return true;
}