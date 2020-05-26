// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

#include <Components/ActorComponent.h>
#include <GameplayTagContainer.h>

#include "CADialogueAudioBucket.h"
#include "CADialogueInstanceInterface.h"
/*#include "CADialogueInstanceDebugInterface.h"*/

#include "CADialogueInstanceComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCADialogueInstanceEventSignature);

/**
* Dialogue Instance Component Base Class
* - A wrapper for a dialogue instance
* - Manages the lifetime of the instance
* - Place it wherever makes sense for the game's existing structure
* -- For example: the game state, or an actor that is streamed in
* - This component also owns all the audio data for the instance
*/
UCLASS(BlueprintType, Blueprintable)
class CADIALOGUE_API UCADialogueInstanceComponent : public UActorComponent
	, public ICADialogueInstanceInterface
	/*, public ICADialogueInstanceDebugInterface*/
{
	GENERATED_BODY()

public:
	UCADialogueInstanceComponent();

	/** The gameplay tag that identifies this instance */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CADialogue")
	FGameplayTag InstanceTag;

	/** Toggle to false to prevent the instance from being created on BeginPlay() */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CADialogue", meta = (AdvancedDisplay))
	bool bRegisterOnBeginPlay;

	/** Toggle to false to prevent the instance from begin deregistered on EndPlay() */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CADialogue", meta = (AdvancedDisplay))
	bool bDeregisterOnEndPlay;

	/** Toggle to false to prevent the instance from begin deregistered on EndPlay() */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CADialogue", meta = (AdvancedDisplay))
	bool bCheckQueueDuringTick;
	
	/** A map of Speaker ->  Event Map -> AudioBuckets */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CADialogue")
	TMap<FGameplayTag, FCADialogueSpeakerAudioBuckets> SpeakerAudioBucketMap;

	/** An event that is broadcasted when a dialogue event has been received on this instance */
	UPROPERTY(BlueprintAssignable, Category = "CADialogue")
	FCADialogueInstanceEventSignature DialogueEventReceivedEvent;


public:
	/** Checks to see if the tag is in the instance's rules */
	UFUNCTION(BlueprintCallable, Category = "CADialogue")
	bool HasRule(FGameplayTag RequiredRule);

	/** Checks to see if all the tags in this container are in the instance's rules */
	UFUNCTION(BlueprintCallable, Category = "CADialogue")
	bool HasRules(FGameplayTagContainer RequiredRulesContianer);

private:
	/** Callback for when audio finishes playing for a speaker */
	UFUNCTION()
	void DialogueFinishedCallbackFunc(FGameplayTag EventTag, FGameplayTag SpeakerTag) { DialogueFinishedCallback(EventTag, SpeakerTag); }

	// ======================================
	// Begin ICADialogueInstanceInterface Interface
public:
	virtual void ReceiveEvent(FCADialogueEvent Event) override;
	virtual bool FilterEvent(FCADialogueEvent Event) override;

	virtual void DialogueFinishedCallback(FGameplayTag EventTag, FGameplayTag SpeakerTag) override {};

	virtual void AddEventToQueue(FCADialogueEvent Event) override;
	virtual void ClearExpiredEventsInQueue() override;

	virtual void AddRule(FGameplayTag InRuleTag) override;
	virtual void AddRules(FGameplayTagContainer InRulesContainer) override;

private:
	virtual void RegisterInstance() override;
	virtual void DeregisterInstance() override;
	// End ICADialogueInstanceInterface Interface
	// ======================================


	// ======================================
	// Begin UActorComponent Interface
public:
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End UActorComponent Interface
	// ======================================

#if CADIALOGUE_DEBUG
	// Begin ICADialogueInstanceDebugInterface
	// virtual void MakeDebugReport() override;
	// End ICADialogueInstanceDebugInterface
#endif

protected:
	/** Gets a sound for a speaker and event*/
	class USoundBase* GetSoundForSpeakerWithEvent(FGameplayTag SpeakerTag, FGameplayTag EventTag);

	/** Broadcasts the SoundToPlay to speakers */
	void BroadcastSoundToSpeakers(FGameplayTag SpeakerTag, FGameplayTag EventTag, class USoundBase* SoundToPlay);

private:
	/**
	* Set of events that acts as a queue.
	* If an event can't fire, add it to the queue so it can play when it has a chance to.
	*/
	TArray<FCADialogueEvent> EventQueue;

	/**
	* Container of rules as tags
	* When a rule is met (on the client implementation), push the corresponding tag to this instance
	* Use this container to filter any events by rules met
	*/
	FGameplayTagContainer RulesTags;
};