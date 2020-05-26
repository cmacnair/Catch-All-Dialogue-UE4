// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include <GameplayTagContainer.h>

#include "CADialogueTypes.h"

#include "CADialogueSpeakerCollection.generated.h"

/**
* A collection of speaker components, representing a single speaker
* Since there could be more than one speaker component with the same name, we need this collection
*/
USTRUCT()
struct CADIALOGUE_API FCADialogueSpeakerCollection
{
	GENERATED_BODY()

public:
	FCADialogueSpeakerCollection() {}

	void AddSpeakerComponent(class UCADialogueSpeakerComponent* InComponent);
	void RemoveSpeakerComponent(class UCADialogueSpeakerComponent* InComponent);
	void PlaySoundOnAllSpeakers(FCADialogueSpeakerParams SpeakerParams);
	bool HasSpeakers() const;

	/** Gets the current instance of the components */
	FGameplayTag GetCurrentInstance() const;

private:
	TArray<class UCADialogueSpeakerComponent*> SpeakerComponents;
};

