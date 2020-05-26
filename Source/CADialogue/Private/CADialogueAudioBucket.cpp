
#include "CADialogueAudioBucket.h"
#include <Sound/SoundBase.h>

USoundBase* FCADialogueAudioBucket::GetSound()
{
	// @todo weighting
	// @todo round robin
	for (auto& SoundIter : Sounds)
	{
		return SoundIter.Sound;
	}

	return nullptr;
}

bool FCADialogueSpeakerAudioBuckets::GetBucketForEvent(FGameplayTag InEvent, FCADialogueAudioBucket& ReturnBucket) const
{
	if (!EventAudioBucketMap.Contains(InEvent))
		return false;

	ReturnBucket = EventAudioBucketMap[InEvent];
	return true;
}
