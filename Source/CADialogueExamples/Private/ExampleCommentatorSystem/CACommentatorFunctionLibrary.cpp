#include "ExampleCommentatorSystem/CACommentatorFunctionLibrary.h"

#include "CADialogueSubsystem.h"
#include "CADialogueEvent.h"
#include "CADialogueExamplesTypes.h"

#include "ExampleCommentatorSystem/CACommentatorTypes.h"

#include "ExampleCommentatorSystem/CACommentatorInstanceComponent.h"


void UCACommentatorFunctionLibrary::SendCommentatorEventByTags(FGameplayTag Event, FGameplayTag Speaker, UObject* Caller)
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("SendCommentatorEventTag"), STAT_CADialogueExamplesSendCommentatorEventTag, STATGROUP_CADialogueExamples);
 	FGameplayTag CommentatorSystemTag = UCACommentatorDeveloperSettings::Get()->CommentatorSystemTag;
	if (CommentatorSystemTag == FGameplayTag::EmptyTag)
		return;

	FCADialogueEvent NewEvent;
	NewEvent.EventTag = Event;
	NewEvent.SpeakerTag = Speaker;
	UCADialogueSubsystem::SendEventToInstance(NewEvent, CommentatorSystemTag, Caller);
}

void UCACommentatorFunctionLibrary::SendCommentatorEvent(FCADialogueEvent Event, class UObject* Caller)
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("SendCommentatorEvent"), STAT_CADialogueExamplesSendCommentatorEvent, STATGROUP_CADialogueExamples);
	FGameplayTag CommentatorSystemTag = UCACommentatorDeveloperSettings::Get()->CommentatorSystemTag;
	if (CommentatorSystemTag == FGameplayTag::EmptyTag)
		return;

	UCADialogueSubsystem::SendEventToInstance(Event, CommentatorSystemTag, Caller);
}
