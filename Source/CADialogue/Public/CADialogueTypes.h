// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

#include <GameplayTagContainer.h>

#include "CADialogueTypes.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(CADialogueLog, Log, All);

#if !UE_BUILD_SHIPPING
#define CADIALOGUE_DEBUG 1
#else 
#define CADIALOGUE_DEBUG 0
#endif



/** Defines data to pass to a Speaker to play a dialogue sound*/
USTRUCT()
struct CADIALOGUE_API FCADialogueSpeakerParams
{
	GENERATED_BODY()

public:
	FCADialogueSpeakerParams()
		: SoundToPlay(nullptr)
		, InstanceTag(FGameplayTag::EmptyTag)
		, EventTag(FGameplayTag::EmptyTag)
		, bShouldReleaseOnFinish(true)
		, DialogueFinishedCallback(nullptr)
	{

	}

	FCADialogueSpeakerParams(class USoundBase* InSound, FGameplayTag InInstanceTag, FGameplayTag InEventTag)
		: bShouldReleaseOnFinish(true)
	{
		SoundToPlay = InSound;
		InstanceTag = InInstanceTag;
		EventTag = InEventTag;
	}

	// @todo more constructors..

	UPROPERTY()
	class USoundBase* SoundToPlay;

	FGameplayTag InstanceTag;
	FGameplayTag EventTag;

	bool bShouldReleaseOnFinish;

	/** Callback to perform when this dialogue line has finished */
	TFunction<void(FGameplayTag EventTag, FGameplayTag SpeakerTag)> DialogueFinishedCallback;
};
