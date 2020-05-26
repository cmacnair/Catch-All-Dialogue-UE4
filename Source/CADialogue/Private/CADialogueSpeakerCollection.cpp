#include "CADialogueSpeakerCollection.h"

#include <Sound/SoundBase.h>
#include "CADialogueSpeakerComponent.h"


void FCADialogueSpeakerCollection::AddSpeakerComponent(UCADialogueSpeakerComponent* InComponent)
{
	SpeakerComponents.Add(InComponent);
}

void FCADialogueSpeakerCollection::RemoveSpeakerComponent(UCADialogueSpeakerComponent* InComponent)
{
	SpeakerComponents.Remove(InComponent);
}

void FCADialogueSpeakerCollection::PlaySoundOnAllSpeakers(FCADialogueSpeakerParams SpeakerParams)
{
	for (auto& SpeakerIter : SpeakerComponents)
	{
		SpeakerIter->StartPlayingDialogue(SpeakerParams);
	}
}

bool FCADialogueSpeakerCollection::HasSpeakers() const
{
	return SpeakerComponents.Num();
}

FGameplayTag FCADialogueSpeakerCollection::GetCurrentInstance() const
{
	check(SpeakerComponents[0]);
	return SpeakerComponents[0]->GetCurrentInstance();

}
