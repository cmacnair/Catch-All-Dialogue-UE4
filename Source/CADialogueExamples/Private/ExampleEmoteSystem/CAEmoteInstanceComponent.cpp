#include "ExampleEmoteSystem/CAEmoteInstanceComponent.h"
#include "CADialogueSubsystem.h"

UCAEmoteInstanceComponent::UCAEmoteInstanceComponent()
{
	// Set the default minimum gap between events to 2.5 seconds
	MinimumGap = 2.5f;
}

void UCAEmoteInstanceComponent::ReceiveEvent(FCADialogueEvent Event)
{
	Super::ReceiveEvent(Event);

	// Filter out the event if it's too low priority
	if (!FilterEvent(Event))
		return;

	// OK to play, so set the new priority and broadcast sounds
	CurrentPriority = GetPriorityForEventTag(Event.EventTag);

	USoundBase* SoundToPlay = GetSoundForSpeakerWithEvent(Event.SpeakerTag, Event.EventTag);
	if (!SoundToPlay)
		return; // whoops! no sound assigned..

	BroadcastSoundToSpeakers(Event.SpeakerTag, Event.EventTag, SoundToPlay);
}

bool UCAEmoteInstanceComponent::FilterEvent(FCADialogueEvent Event)
{
	// First check if it passes the global filter
	if (!Super::FilterEvent(Event))
		return false;

	// Now check the event's priority against our current, tracked priority
	ECAEmotePriority EventPriority = GetPriorityForEventTag(Event.EventTag);
	if (!CheckPriority(EventPriority))
		return false;

	// Now check the time since the speaker last played an emote
	// If it's below the minimum time, then filter this event
	// If it's above, allow it to play and then reset the time
	float CurrentTime = UCADialogueSubsystem::GetCurrentTime(this);

	if (PlayerLastEmoteTimeMap.Contains(Event.SpeakerTag))
	{
		float LastPlayedTime = PlayerLastEmoteTimeMap[Event.SpeakerTag];
		if ((CurrentTime - LastPlayedTime) < MinimumGap)
			return false;

		PlayerLastEmoteTimeMap[Event.SpeakerTag] = CurrentTime;
	}
	else
	{
		PlayerLastEmoteTimeMap.Add(Event.SpeakerTag, CurrentTime);
	}
	return true;
}

ECAEmotePriority UCAEmoteInstanceComponent::GetPriorityForEventTag(FGameplayTag Event) const
{
	if (!EventToPriorityMap.Contains(Event))
	{
		return ECAEmotePriority::Off;
	}

	return EventToPriorityMap[Event];
}

bool UCAEmoteInstanceComponent::CheckPriority(ECAEmotePriority InPriority)
{
	return InPriority > CurrentPriority;
}
