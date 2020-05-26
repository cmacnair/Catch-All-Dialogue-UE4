#include "ExampleCommentatorSystem/CACommentatorInstanceComponent.h"

#include <Sound/SoundBase.h>

#include "CADialogueSubsystem.h"
#include "CADialogueSpeakerCollection.h"


UCACommentatorInstanceComponent::UCACommentatorInstanceComponent()
{
	CurrentPriority = ECACommentatorPriority::Off;

	MinTimeToTriggerChatter = 4.0f;
	MaxTimeToTriggerChatter = 10.0f;

	NextEventCountdownTime = 0.0f;
}

void UCACommentatorInstanceComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!PossibleIdleChatterSpeakers.Num() || !PossibleIdleChatterEvents.Num())
		return;

	NextEventCountdownTime -= DeltaTime;
	if (NextEventCountdownTime <= 0)
		RequestIdleChatterEvent();

}

void UCACommentatorInstanceComponent::ReceiveEvent(FCADialogueEvent Event)
{
	Super::ReceiveEvent(Event);

	// Filter out the event if it's too low priority
	if (!FilterEvent(Event))
		return;

	NextEventCountdownTime = FMath::RandRange(MinTimeToTriggerChatter, MaxTimeToTriggerChatter);

	// OK to play, so set the new priority and broadcast sounds
	CurrentPriority = GetPriorityForEventTag(Event.EventTag);
	
	USoundBase* SoundToPlay = GetSoundForSpeakerWithEvent(Event.SpeakerTag, Event.EventTag);
	if (!SoundToPlay)
		return; // whoops! no sound assigned..
	
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

void UCACommentatorInstanceComponent::RequestIdleChatterEvent()
{
	ensure(PossibleIdleChatterSpeakers.Num() && PossibleIdleChatterEvents.Num());

	int32 SpeakerIndex = FMath::RandRange(0, PossibleIdleChatterSpeakers.Num()-1);
	FGameplayTag SpeakerTag = PossibleIdleChatterSpeakers[SpeakerIndex];
	int32 EventIndex = FMath::RandRange(0, PossibleIdleChatterSpeakers.Num() - 1);
	FGameplayTag EventTag = PossibleIdleChatterEvents[EventIndex];

	FCADialogueEvent NewIdleChatterEvent;
	NewIdleChatterEvent.EventTag = EventTag;
	NewIdleChatterEvent.SpeakerTag = SpeakerTag;

	ReceiveEvent(NewIdleChatterEvent);
}

void UCACommentatorInstanceComponent::DialogueFinishedCallback(FGameplayTag EventTag, FGameplayTag SpeakerTag)
{
	CurrentPriority = ECACommentatorPriority::Off;
}
