#include "ExampleCommentatorSystem/CACommentatorFunctionLibrary.h"

#include "CADialogueSubsystem.h"
#include "CADialogueEvent.h"

#include "ExampleCommentatorSystem/CACommentatorInstanceComponent.h"


void UCACommentatorFunctionLibrary::SendCommentatorEventByTags(FGameplayTag Event, FGameplayTag Speaker, UObject* Caller)
{
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
	FGameplayTag CommentatorSystemTag = UCACommentatorDeveloperSettings::Get()->CommentatorSystemTag;
	if (CommentatorSystemTag == FGameplayTag::EmptyTag)
		return;

	UCADialogueSubsystem::SendEventToInstance(Event, CommentatorSystemTag, Caller);
}
