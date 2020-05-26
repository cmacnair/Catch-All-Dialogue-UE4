// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

#include <GameplayTagContainer.h>
#include <Engine/DataAsset.h>

#include "CADialogueAudioBucket.h"

#include "CADialogueSpeakerDataAsset.generated.h"


/**
*/
UCLASS()
class CADIALOGUE_API UCADialogueSpeakerDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UCADialogueSpeakerDataAsset() {}

	/** A map of Speaker ->  Event Map -> AudioBuckets */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CADialogue")
	TMap<FGameplayTag, FCADialogueSpeakerAudioBuckets> SpeakerAudioData;
};
