// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

#include <GameplayTagContainer.h>

#include "CADialogueWeightedSound.h"

#include "CADialogueAudioBucket.generated.h"

/**
* @todo - add round robin

* Dialogue audio data bucket base class
* Bucket tag should correspond with the event-to-bucket mapping
* Additional tags can be assigned to have even more specific mapping
*
* Such as:
*		Event			= PlayerOpenChest
*		AdditionalTags	= Player.Link, Weapon.Woodarrows
*		Result			= Play sound for Link Opening Chest for wood arrows
*
* Implementation example:
*	TMap<FGameplayTag, FCADialogueAudioBucket> EventAudioBucketsMap;
*/
USTRUCT(BlueprintType)
struct CADIALOGUE_API FCADialogueAudioBucket
{
	GENERATED_BODY()

public:
	FCADialogueAudioBucket()
		: BucketTag(FGameplayTag::EmptyTag)
	{}
	
	/** Bucket tag identifying this bucket */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CADialogue")
	FGameplayTag BucketTag;

	/** List of sounds, typically populated by an imported data table */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CADialogue")
	TArray<FCADialogueWeightedSound> Sounds;

	/** Get a sound from this bucket */
	class USoundBase* GetSound();

};

/**
* A container for audio buckets for a given speaker
* More often, speaker tags dictate which assets should be available at runtime
* So organizing Speakers -> Events - > Event Data allows the client to better manage loading
*/
USTRUCT(BlueprintType)
struct CADIALOGUE_API FCADialogueSpeakerAudioBuckets
{
	GENERATED_BODY()

public:
	FCADialogueSpeakerAudioBuckets() {}

	/**
	* EventTag is the key, the corresponding audio bucket is the data
	* The key to this map must match the bucket's BucketTag
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CADialogue")
	TMap<FGameplayTag, FCADialogueAudioBucket> EventAudioBucketMap;


	bool GetBucketForEvent(FGameplayTag InEvent, FCADialogueAudioBucket& ReturnBucket) const;
};