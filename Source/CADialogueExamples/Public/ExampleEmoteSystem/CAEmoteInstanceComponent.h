// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

#include "CADialogueInstanceComponent.h"
#include "CAEmoteTypes.h"

#include "CAEmoteInstanceComponent.generated.h"

/**
* An example of an Emote System
* Emotes are grunts, efforts, moans etc., commonly used to support player interactions
* This system throttles the commands by priority and a required elapsed time 
*/
UCLASS(BlueprintType, Blueprintable, classGroup="EmoteDialogue")
class CADIALOGUEEXAMPLES_API UCAEmoteInstanceComponent : public UCADialogueInstanceComponent
{
	GENERATED_BODY()

public:
	UCAEmoteInstanceComponent();


	// Begin ICADialogueInstanceInterface Interface
public:
	virtual void ReceiveEvent(FCADialogueEvent Event) override;
	virtual bool FilterEvent(FCADialogueEvent Event) override;
	// End ICADialogueInstanceInterface Interface


	/** Map each event tag to a priority */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CADialogue")
	TMap<FGameplayTag, ECAEmotePriority> EventToPriorityMap;

	/** The minimum gap between sounds, in seconds */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CADialogue", meta = (UIMin=0.0f, UIMax=100.0f))
	float MinimumGap;


private:
	/** Returns the priority for the event tag */
	ECAEmotePriority GetPriorityForEventTag(FGameplayTag Event) const;

	/** Checks to see if the given priority is greater than the instance's current priority */
	bool CheckPriority(ECAEmotePriority InPriority);

	/** Time since last emote performed by speaker */
	TMap<FGameplayTag, float> PlayerLastEmoteTimeMap;

	/** The current priority of the commentator system */
	ECAEmotePriority CurrentPriority;

};