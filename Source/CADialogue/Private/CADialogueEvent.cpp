#include "CADialogueEvent.h"

#include <Kismet/KismetSystemLibrary.h>

FCADialogueEvent::FCADialogueEvent()
	: SpeakerTag(FGameplayTag::EmptyTag)
	, EventTag(FGameplayTag::EmptyTag)
	, AdditionalTags(FGameplayTagContainer::EmptyContainer)
	, QueueWaitTime(0.0f)
	, EventRequestTimeStamp(0.0f)
{
}

void FCADialogueEvent::SetTimeStamp(float InTime)
{
	EventRequestTimeStamp = InTime;
}

float FCADialogueEvent::GetTimeStamp() const
{
	return EventRequestTimeStamp;
}
