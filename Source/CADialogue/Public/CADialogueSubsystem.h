// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

#include <Subsystems/GameInstanceSubsystem.h>
#include <GameplayTagContainer.h>

#include "CADialogueTypes.h"
#include "CADialogueEvent.h"
#include "CADialogueSpeakerCollection.h"

#include "CADialogueSubsystem.generated.h"

/**
* @todo
* Save interface component
* Debugging
* Commandlet
* Examples
*/

/**
* Dialogue Subsystem, a Game Instance Subsystem class
* This class is the top level container for all dialogue instances
* - Cache dialogue instances
* - Access dialogue instances
* - Dispatch events to instances
* - Trigger reports
*/
UCLASS()
class CADIALOGUE_API UCADialogueSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UCADialogueSubsystem() {}

	/** Returns this subsystem from the GEngine game instance */
	static UCADialogueSubsystem* GetDialogueSubsystem(class UObject* Caller);

	/** Returns current time, mostly for making timestamps for events */
	static float GetCurrentTime(class UObject* Caller);

	/** Returns a cached instance by it's FGameplayTag id */
	static class UCADialogueInstanceComponent* GetInstanceByTag(FGameplayTag InstanceTag, class UObject* Caller);
	
	/** Send an event to a given instance, using Caller's world */
	static void SendEventToInstance(FCADialogueEvent Event, FGameplayTag InstanceTag, class UObject* Caller);

#pragma region InstancesAPI
	/**
	* Registers a dialogue instance to this subsystem
	* Once registered, it can be accessed through the API
	*/
	void RegisterInstance(class UCADialogueInstanceComponent* InInstance);

	/**
	* Deregisters an instance
	* Once deregistered, it will no longer be accessible
	*/
	void DeregisterInstance(FGameplayTag InInstanceTag);

	/** Returns the cached instance object associated to the tag */
	class UCADialogueInstanceComponent* GetDialogueInstanceByTag(FGameplayTag InstanceTag);
#pragma endregion InstancesAPI


#pragma region SpeakersAPI
	/** Register a speaker with the dialogue subsystem, making it accessible by dialogue instances */
	void RegisterSpeaker(class UCADialogueSpeakerComponent* InSpeaker);
	
	/** Deregister a speaker with the dialogue subsystem, making it not accessible by dialogue instances */
	void DeregisterSpeaker(class UCADialogueSpeakerComponent* InSpeaker);

	/** Gets the collection of speakers for a given tag*/
	void GetSpeakersForTag(FGameplayTag SpeakerTag, FCADialogueSpeakerCollection& ReturnValue);

	/** Checks to see if the speaker can be played on this instance, due to priority settings */
	bool CanSpeakerPlayForInstance(FGameplayTag SpeakerTag, FGameplayTag InstanceTag);
#pragma endregion SpeakersAPI


#pragma region DebugAPI
#if CADIALOGUE_DEBUG
	// @todo add params to arg for determining debug information
	void MakeDebugReport();
#endif
#pragma endregion DebugAPI


private:
	/** A map of the registered dialogue instances */
	UPROPERTY()
	TMap<FGameplayTag, class UCADialogueInstanceComponent*> DialogueInstancesMap;

	UPROPERTY()
	/** Map of weak pointers to dialogue speakers */
	TMap<FGameplayTag, FCADialogueSpeakerCollection> DialogueSpeakers;
};