#include "ExampleCommentatorSystem/CACommentatorInstanceComponent.h"

#include <Sound/SoundBase.h>

#include "CADialogueSubsystem.h"
#include "CADialogueSpeakerCollection.h"


UCACommentatorInstanceComponent::UCACommentatorInstanceComponent()
{
	CurrentPriority = ECACommentatorPriority::Off;
}

void UCACommentatorInstanceComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// @todo measure time since last event, then play idle chatter


}

void UCACommentatorInstanceComponent::ReceiveEvent(FCADialogueEvent Event)
{
	Super::ReceiveEvent(Event);

	// Filter out the event if it's too low priority
	if (!FilterEvent(Event))
		return;

	// OK to play, so set the new priority and broadcast sounds
	CurrentPriority = GetPriorityForEventTag(Event.EventTag);
	
	USoundBase* SoundToPlay = GetSoundForSpeakerWithEvent(Event.SpeakerTag, Event.EventTag);
	if (!SoundToPlay)
		return; // whoops! no sound loaded assigned..
	
	BroadcastSoundToSpeakers(Event.SpeakerTag, Event.EventTag, SoundToPlay);
}

bool UCACommentatorInstanceComponent::FilterEvent(FCADialogueEvent Event)
{
	// First check if it passes the global filter
	if (!Super::FilterEvent(Event))
		return false;

	// Now check the event's priority against our current, tracked priority
	ECACommentatorPriority EventPriority = GetPriorityForEventTag(Event.EventTag);
	if (!CheckPriority(EventPriority))
	{
		AddEventToQueue(Event);
		return false;
	}

	return true;
}

ECACommentatorPriority UCACommentatorInstanceComponent::GetPriorityForEventTag(FGameplayTag Event) const
{
	if (!EventToPriorityMap.Contains(Event))
	{
		return ECACommentatorPriority::Off;
	}

	return EventToPriorityMap[Event];
}

bool UCACommentatorInstanceComponent::CheckPriority(ECACommentatorPriority InPriority)
{
	return InPriority > CurrentPriority;
}

void UCACommentatorInstanceComponent::DialogueFinishedCallback(FGameplayTag EventTag, FGameplayTag SpeakerTag)
{
	CurrentPriority = ECACommentatorPriority::Off;
}
