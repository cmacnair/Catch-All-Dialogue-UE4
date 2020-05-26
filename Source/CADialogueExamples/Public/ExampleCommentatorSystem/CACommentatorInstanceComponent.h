// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

#include "CADialogueInstanceComponent.h"
#include "CACommentatorTypes.h"

#include "CACommentatorInstanceComponent.generated.h"

/**
* A Commentator Dialogue Instance
*
* The purpose of this example is to demonstrate an implementation of a voice over commentator-like system
* For example, commentary over a boxing match or dynamic narrative for an RPG
*/
UCLASS(BlueprintType, Blueprintable, classGroup="CommentatorDialogue")
class CADIALOGUEEXAMPLES_API UCACommentatorInstanceComponent : public UCADialogueInstanceComponent
{
	GENERATED_BODY()

public:
	UCACommentatorInstanceComponent();


	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Begin ICADialogueInstanceInterface Interface
public:
	virtual void ReceiveEvent(FCADialogueEvent Event) override;
	virtual bool FilterEvent(FCADialogueEvent Event) override;
	virtual void DialogueFinishedCallback(FGameplayTag EventTag, FGameplayTag SpeakerTag) override;
	// End ICADialogueInstanceInterface Interface


	/** Map each event tag to a priority */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CADialogue")
	TMap<FGameplayTag, ECACommentatorPriority> EventToPriorityMap;

	/** The lower bound of a random range for when idle chatter occurs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CADialogue")
	float MinTimeToTriggerChatter;

	/** The upper bound of a random range for when idle chatter occurs */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CADialogue")
	float MaxTimeToTriggerChatter;

	/** A set of speakers that could be chosen from to perform idle chatter */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CADialogue")
	TArray<FGameplayTag> PossibleIdleChatterSpeakers;

	/** A set of events that could be chosen from to perform idle chatter */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CADialogue")
	TArray<FGameplayTag> PossibleIdleChatterEvents;

private:
	/** Returns the priority for the event tag */
	ECACommentatorPriority GetPriorityForEventTag(FGameplayTag Event) const;

	/** Checks to see if the given priority is greater than the instance's current priority */
	bool CheckPriority(ECACommentatorPriority InPriority);

	/** Requests a random idle chatter event */
	void RequestIdleChatterEvent();

	/** The current priority of the commentator system */
	ECACommentatorPriority CurrentPriority;

	/** Count down until this is zero, then fire an event */
	float NextEventCountdownTime;

};