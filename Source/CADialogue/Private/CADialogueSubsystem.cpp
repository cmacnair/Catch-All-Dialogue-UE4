#include "CADialogueSubsystem.h"

#include <Kismet/GameplayStatics.h>
#include <Logging/LogMacros.h>
#include <Kismet/KismetSystemLibrary.h>

#include "CADialogueSpeakerComponent.h"
#include "CADialogueInstanceComponent.h"
#include "CADialogueSpeakerCollection.h"
#include "CADialogueDeveloperSettings.h"


UCADialogueSubsystem* UCADialogueSubsystem::GetDialogueSubsystem(UObject* Caller)
{
	UWorld* World = Caller->GetWorld();
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	ensure(GameInstance);
	return GameInstance->GetSubsystem<UCADialogueSubsystem>();
}

float UCADialogueSubsystem::GetCurrentTime(UObject* Caller)
{
	UCADialogueSubsystem* DialogueSubsystem = GetDialogueSubsystem(Caller);
	return UKismetSystemLibrary::GetGameTimeInSeconds(DialogueSubsystem);
}

class UCADialogueInstanceComponent* UCADialogueSubsystem::GetInstanceByTag(FGameplayTag InstanceTag, class UObject* Caller)
{
	UCADialogueSubsystem* DialogueSubsystem = UCADialogueSubsystem::GetDialogueSubsystem(Caller);
	return DialogueSubsystem->GetDialogueInstanceByTag(InstanceTag);
}

void UCADialogueSubsystem::SendEventToInstance(FCADialogueEvent Event, FGameplayTag InstanceTag, class UObject* Caller)
{
	UCADialogueInstanceComponent* Instance = GetInstanceByTag(InstanceTag, Caller);
	check(Instance)
		Instance->ReceiveEvent(Event);
}

void UCADialogueSubsystem::RegisterInstance(UCADialogueInstanceComponent* InInstance)
{
	FGameplayTag InstanceTag = InInstance->InstanceTag;
	if (DialogueInstancesMap.Contains(InstanceTag))
	{
		UE_LOG(CADialogueLog, Error, TEXT("UCADialogueSubsystem::RegisterInstance Unable to register instance, an instance is already mapped to that tag! Instance Tag: %s"), *InstanceTag.GetTagName().ToString());
		return;
	}
	DialogueInstancesMap.Add(InstanceTag, InInstance);
}

void UCADialogueSubsystem::DeregisterInstance(FGameplayTag InInstanceTag)
{
	if (!DialogueInstancesMap.Contains(InInstanceTag))
	{
		UE_LOG(CADialogueLog, Error, TEXT("UCADialogueSubsystem::DeregisterInstance Attempting to deregister and instance that was never registered! Instance Tag: %s"), *InInstanceTag.GetTagName().ToString());
		return;
	}
	DialogueInstancesMap.Remove(InInstanceTag);
}

UCADialogueInstanceComponent* UCADialogueSubsystem::GetDialogueInstanceByTag(FGameplayTag InstanceTag)
{
	if (!DialogueInstancesMap.Contains(InstanceTag))
	{
		UE_LOG(CADialogueLog, Verbose, TEXT("UCADialogueSubsystem::GetDialogueInstanceByTag Attempting to access an instance that is not active! Instance Tag: %s"), *InstanceTag.GetTagName().ToString());
		return nullptr;
	}

	ensure(DialogueInstancesMap[InstanceTag]);
	return DialogueInstancesMap[InstanceTag];
}

void UCADialogueSubsystem::RegisterSpeaker(class UCADialogueSpeakerComponent* InSpeaker)
{
	if (DialogueSpeakers.Contains(InSpeaker->SpeakerTag))
	{
		DialogueSpeakers[InSpeaker->SpeakerTag].AddSpeakerComponent(InSpeaker);
		return;
	}

	FCADialogueSpeakerCollection NewCollection;
	NewCollection.AddSpeakerComponent(InSpeaker);
	DialogueSpeakers.Add(InSpeaker->SpeakerTag, NewCollection);
}

void UCADialogueSubsystem::DeregisterSpeaker(class UCADialogueSpeakerComponent* InSpeaker)
{
	if (DialogueSpeakers.Contains(InSpeaker->SpeakerTag))
	{
		FCADialogueSpeakerCollection& SpeakerCollection = DialogueSpeakers[InSpeaker->SpeakerTag];
		SpeakerCollection.RemoveSpeakerComponent(InSpeaker);
		if (!SpeakerCollection.HasSpeakers())
		{
			DialogueSpeakers.Remove(InSpeaker->SpeakerTag);
		}
	}
}

void UCADialogueSubsystem::GetSpeakersForTag(FGameplayTag SpeakerTag, FCADialogueSpeakerCollection& ReturnValue)
{
	if (!DialogueSpeakers.Contains(SpeakerTag))
		return;

	ReturnValue = DialogueSpeakers[SpeakerTag];
}

bool UCADialogueSubsystem::CanSpeakerPlayForInstance(FGameplayTag SpeakerTag, FGameplayTag InstanceTag)
{
	// Speaker must be registered
	ensure(DialogueSpeakers.Contains(SpeakerTag));

	FGameplayTag CurrentInstanceTag = DialogueSpeakers[SpeakerTag].GetCurrentInstance();
	if (CurrentInstanceTag == FGameplayTag::EmptyTag)
		return true;

	TMap<FGameplayTag, int> InstancePriorityMap = UCADialogueDeveloperSettings::Get()->InstancePriorityDefinitionInMap;
	if (!InstancePriorityMap.Contains(InstanceTag) || !InstancePriorityMap.Contains(CurrentInstanceTag))
		return true;

	bool isGreaterPriority = InstancePriorityMap[InstanceTag] > InstancePriorityMap[CurrentInstanceTag];
	return isGreaterPriority;
}

#if CADIALOGUE_DEBUG
void UCADialogueSubsystem::MakeDebugReport()
{

}
#endif // CADIALOGUE_DEBUG
