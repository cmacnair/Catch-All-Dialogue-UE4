#include "ExampleEmoteSystem/CAEmoteFunctionLibrary.h"

#include "CADialogueSubsystem.h"
#include "CADialogueEvent.h"

#include "ExampleEmoteSystem/CAEmoteInstanceComponent.h"


void UCAEmoteFunctionLibrary::PlayEmoteForPlayer(FGameplayTag EmoteTag, FGameplayTag PlayerTag, class UObject* Caller)
{
	FGameplayTag EmoteSystemTag = UCAEmoteDeveloperSettings::Get()->EmoteSystemTag;
	if (EmoteSystemTag == FGameplayTag::EmptyTag)
		return;

	FCADialogueEvent NewEvent;
	NewEvent.EventTag = EmoteTag;
	NewEvent.SpeakerTag = PlayerTag;
	UCADialogueSubsystem::SendEventToInstance(NewEvent, EmoteSystemTag, Caller);
}
