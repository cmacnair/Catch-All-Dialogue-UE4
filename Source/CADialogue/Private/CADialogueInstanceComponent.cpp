#include "CADialogueInstanceComponent.h"

#include <Stats/Stats.h>

#include "CADialogueSubsystem.h"
#include "CADialogueSpeakerDataAsset.h"

UCADialogueInstanceComponent::UCADialogueInstanceComponent()
	: bRegisterOnBeginPlay(true)
	, bDeregisterOnEndPlay(true)
	, bCheckQueueDuringTick(true)
{
	SetTickGroup(TG_PostUpdateWork);
	PrimaryComponentTick.bCanEverTick = true;
}

bool UCADialogueInstanceComponent::HasRule(FGameplayTag RequiredRule)
{
	return RulesTags.HasTag(RequiredRule);
}

bool UCADialogueInstanceComponent::HasRules(FGameplayTagContainer RequiredRulesContianer)
{
	return RulesTags.HasAll(RequiredRulesContianer);
}

void UCADialogueInstanceComponent::ReceiveEvent(FCADialogueEvent Event)
{
	DialogueEventReceivedEvent.Broadcast();
}

bool UCADialogueInstanceComponent::FilterEvent(FCADialogueEvent Event)
{
	UCADialogueSubsystem* DialogueSubsystem = UCADialogueSubsystem::GetDialogueSubsystem(this);
	ensure(DialogueSubsystem);
	return DialogueSubsystem->CanSpeakerPlayForInstance(Event.SpeakerTag, InstanceTag);
}

void UCADialogueInstanceComponent::AddEventToQueue(FCADialogueEvent Event)
{
	Event.SetTimeStamp(UCADialogueSubsystem::GetCurrentTime(this));
	EventQueue.Add(Event);
}

void UCADialogueInstanceComponent::ClearExpiredEventsInQueue()
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("ClearExpiredEvents"), STAT_CADialogueClearExpiredEvents, STATGROUP_CADialogue);
	if (!EventQueue.Num())
		return;

	float CurrentTime = UCADialogueSubsystem::GetCurrentTime(this);

	for (uint8 EventQueueIter = EventQueue.Num() - 1; EventQueueIter >= 0; --EventQueueIter)
	{
		float ElapsedTimeSinceEnteredQueue = CurrentTime - EventQueue[EventQueueIter].GetTimeStamp();
		if (ElapsedTimeSinceEnteredQueue > EventQueue[EventQueueIter].QueueWaitTime)
		{
			EventQueue.RemoveAt(EventQueueIter);
		}
	}
}

void UCADialogueInstanceComponent::AddRule(FGameplayTag InRuleTag)
{
	RulesTags.AddTag(InRuleTag);
}

void UCADialogueInstanceComponent::AddRules(FGameplayTagContainer InRulesContainer)
{
	RulesTags.AppendTags(InRulesContainer);
}

void UCADialogueInstanceComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bCheckQueueDuringTick)
	{
		ClearExpiredEventsInQueue();
	}
}

void UCADialogueInstanceComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bRegisterOnBeginPlay)
		RegisterInstance();
}

void UCADialogueInstanceComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	DeregisterInstance();
}

const TArray<class USoundBase*> UCADialogueInstanceComponent::GetListOfAllSounds() const
{
	TArray<class USoundBase*> SoundsFound;
	
	if (SpeakerAudioData)
	{
		for (auto& AudioBucketsIter : SpeakerAudioData->SpeakerAudioData)
		{
			for (auto& AudioBucketIter : AudioBucketsIter.Value.EventAudioBucketMap)
			{
				for (auto& SoundIter : AudioBucketIter.Value.Sounds)
				{
					SoundsFound.Add(SoundIter.Sound);
				}
			}
		}
	}

	return SoundsFound;
}

#if CADIALOGUE_DEBUG
void UCADialogueInstanceComponent::MakeDebugReport()
{
	/*
	
	const FString PathName = FPaths::ProfilingDir() + TEXT("dir/") + DirectoryName;
	IFileManager::Get().MakeDirectory(*PathName);
	const FString FileName = TEXT("dump.txt");
	const FString FilenameFull = PathName + FileName;

	FFileHelper::SaveStringToFile(FileContainer.FileContents, *FilenameFull);
	UE_LOG(dump, Log, TEXT("SVRStats Dump: Saved file to: %s"), *FilenameFull);

	*/
}
#endif

void UCADialogueInstanceComponent::RegisterInstance()
{
	//QUICK_SCOPE_CYCLE_COUNTER(TEXT("CADialogue::RegisterInstance"));

	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("RegisterInstance"), STAT_CADialogueRegisterInstance, STATGROUP_CADialogue);

	UCADialogueSubsystem* DialogueSubsystem = UCADialogueSubsystem::GetDialogueSubsystem(this);
	ensure(DialogueSubsystem);
	DialogueSubsystem->RegisterInstance(this);
}

void UCADialogueInstanceComponent::DeregisterInstance()
{
	UCADialogueSubsystem* DialogueSubsystem = UCADialogueSubsystem::GetDialogueSubsystem(this);
	ensure(DialogueSubsystem);
 	DialogueSubsystem->DeregisterInstance(InstanceTag);
}

class USoundBase* UCADialogueInstanceComponent::GetSoundForSpeakerWithEvent(FGameplayTag SpeakerTag, FGameplayTag EventTag)
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("GetSoundForEvent"), STAT_CADialogueGetSoundForEvent, STATGROUP_CADialogue);
	if (!SpeakerAudioData)
		return nullptr;

	if (!SpeakerAudioData->SpeakerAudioData.Contains(SpeakerTag))
		return nullptr;

	FCADialogueSpeakerAudioBuckets& SpeakerBuckets = SpeakerAudioData->SpeakerAudioData[SpeakerTag];

	FCADialogueAudioBucket EventBucket;
	bool bFoundBucketForEvent = SpeakerBuckets.GetBucketForEvent(EventTag, EventBucket);
	if (!bFoundBucketForEvent)
		return nullptr;

	return EventBucket.GetSound();
}

void UCADialogueInstanceComponent::BroadcastSoundToSpeakers(FGameplayTag SpeakerTag, FGameplayTag EventTag, class USoundBase* SoundToPlay)
{

	UCADialogueSubsystem* DialogueSubsystem = UCADialogueSubsystem::GetDialogueSubsystem(this);

	FCADialogueSpeakerCollection Speakers;
	DialogueSubsystem->GetSpeakersForTag(SpeakerTag, Speakers);
	FCADialogueSpeakerParams SpeakerParams(SoundToPlay, InstanceTag, EventTag);
	SpeakerParams.DialogueFinishedCallback = [this](FGameplayTag EventTag, FGameplayTag SpeakerTag)
	{
		DialogueFinishedCallbackFunc(EventTag, SpeakerTag);
	};

	Speakers.PlaySoundOnAllSpeakers(SpeakerParams);
}
