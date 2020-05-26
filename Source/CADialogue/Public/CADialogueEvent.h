// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

#include <GameplayTagContainer.h>

#include "CADialogueEvent.generated.h"

/**
* A base class for Dialogue Events
* Events are sent to Instances to request some dialogue
* For example, with a commentator system:
* When the player lands a heavy punch, send a dialogue event for Punch to Commentator Instance
*/
USTRUCT(BlueprintType)
struct CADIALOGUE_API FCADialogueEvent
{
	GENERATED_BODY()

public:

	FCADialogueEvent();

	/** The tag to identify this event */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CADialogue")
	FGameplayTag SpeakerTag;

	/** The tag to identify this event */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CADialogue")
	FGameplayTag EventTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CADialogue")
	FGameplayTagContainer AdditionalTags;

	/** The time this event will wait in the queue before it is discarded */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CADialogue")
	float QueueWaitTime;

	/** Sets the request time stamp */
	void SetTimeStamp(float InTime);
	float GetTimeStamp() const;

private:
	/** The time at which this event was requested */
	float EventRequestTimeStamp;
};