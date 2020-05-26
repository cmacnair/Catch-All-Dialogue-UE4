// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

#include <GameplayTagContainer.h>
#include <Components/AudioComponent.h>

#include "CADialogueSpeakerComponent.generated.h"


/**
* A dialogue speaker component, a subclass of AudioComponent
* - Container for an audio component that plays dialogue in this system
* - Exists as a reference in the global subsystem
* - When played as part of a Dialogue Event, it is considered busy 
*
* @todo fades
* @todo interrupting
* @todo event for when reset, so it can be used for a queue
*/
UCLASS(BlueprintType, Blueprintable, classGroup="CADialogue", meta = (BlueprintSpawnableComponent))
class CADIALOGUE_API UCADialogueSpeakerComponent : public UAudioComponent
{
	GENERATED_BODY()

public:
	UCADialogueSpeakerComponent();

	// Begin UActorComponent Interface
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End UActorComponent Interface

public:
	/** The tag to identify this event */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CADialogue")
	FGameplayTag SpeakerTag;

	
	/** Check if this speaker is playing as part of a dialogue event */
	UFUNCTION(BlueprintCallable, Category = "CADialogue")
	bool IsPlayingDialogue();

	/** Only call this from an instance, tell the component to start playing */
	void StartPlayingDialogue(FCADialogueSpeakerParams SpeakerParams);

	FGameplayTag GetCurrentInstance() const { return CurrentInstance; }

	// @todo interrupting..


	UFUNCTION()
	void OnAudioFinishedEvent(UAudioComponent* InComponent);

private:
	/** Clears the instance and flags, releasing it for use */
	void Reset();

	/** True if this component is being used for an event right now */
	bool bIsInEvent;
	/** When the line finished, should we release this from the instance? */
	bool bShouldReleaseOnFinish;
	/** The tag identifying the instance that's currently using this */
	FGameplayTag CurrentInstance;
	/** The tag identifying the event that's currently using this */
	FGameplayTag CurrentEventTag;
	/** Call this function when finished playing the line of dialogue */
	TFunction<void(FGameplayTag EventTag, FGameplayTag SpeakerTag)> DialogueFinishedCallback;
};
