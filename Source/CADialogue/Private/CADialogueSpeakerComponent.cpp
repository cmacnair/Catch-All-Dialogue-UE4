#include "CADialogueSpeakerComponent.h"
#include "CADialogueSubsystem.h"

UCADialogueSpeakerComponent::UCADialogueSpeakerComponent()
	: bIsInEvent(false)
	, bShouldReleaseOnFinish(true)
	, CurrentInstance(FGameplayTag::EmptyTag)
	, CurrentEventTag(FGameplayTag::EmptyTag)
	, DialogueFinishedCallback(nullptr)
{

}

void UCADialogueSpeakerComponent::BeginPlay()
{
	Super::BeginPlay();

	UCADialogueSubsystem* DialogueSubsystem = UCADialogueSubsystem::GetDialogueSubsystem(this);
	DialogueSubsystem->RegisterSpeaker(this);
}

void UCADialogueSpeakerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	UCADialogueSubsystem* DialogueSubsystem = UCADialogueSubsystem::GetDialogueSubsystem(this);
	DialogueSubsystem->DeregisterSpeaker(this);
}

bool UCADialogueSpeakerComponent::IsPlayingDialogue()
{
	return bIsInEvent;
}

void UCADialogueSpeakerComponent::StartPlayingDialogue(FCADialogueSpeakerParams SpeakerParams)
{
	ensure(SpeakerParams.SoundToPlay && SpeakerParams.InstanceTag != FGameplayTag::EmptyTag);

	if (IsPlaying())
	{
		Stop();
		SpeakerInterruptedEvent.Broadcast(CurrentEventTag);
	}

	SetSound(SpeakerParams.SoundToPlay);
	CurrentInstance = SpeakerParams.InstanceTag;
	CurrentEventTag = SpeakerParams.EventTag;
	bShouldReleaseOnFinish = SpeakerParams.bShouldReleaseOnFinish;
	DialogueFinishedCallback = SpeakerParams.DialogueFinishedCallback;

	bIsInEvent = true;
	Play();

	SpeakerStartedEvent.Broadcast(CurrentEventTag);
	OnAudioFinishedNative.AddUObject(this, &UCADialogueSpeakerComponent::OnAudioFinishedEvent);
}

void UCADialogueSpeakerComponent::OnAudioFinishedEvent(UAudioComponent* InComponent)
{
	SpeakerSoppedEvent.Broadcast(CurrentEventTag);

	if (DialogueFinishedCallback)
	{
		DialogueFinishedCallback(CurrentEventTag, SpeakerTag);
	}

	if (bShouldReleaseOnFinish)
	{
		Reset();
	}
}

void UCADialogueSpeakerComponent::Reset()
{
	bIsInEvent = false;
	CurrentInstance = FGameplayTag::EmptyTag;
	CurrentEventTag = FGameplayTag::EmptyTag;
	bShouldReleaseOnFinish = true;
	DialogueFinishedCallback = nullptr;
}
