#pragma once

#include "CoreMinimal.h"
#include <GameplayTagContainer.h>
#include <UObject/Interface.h>

#include "CADialogueTypes.h"
#include "CADialogueEvent.h"

#include "CADialogueInstanceInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UCADialogueInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

class ICADialogueInstanceInterface
{
	GENERATED_BODY()

public:
	/** Receives an event targeted to this, like a dialogue trigger */
	virtual void ReceiveEvent(FCADialogueEvent Event) = 0;

	/** Apply a filter to an event, if it results in true, then play the dialogue */
	virtual bool FilterEvent(FCADialogueEvent Event) = 0;

	/** Callback to perform when a dialogue event finishes */
	virtual void DialogueFinishedCallback(FGameplayTag EventTag, FGameplayTag SpeakerTag) = 0;

	/** Add a rule or container of rules to the instance filter */
	virtual void AddRule(FGameplayTag InRuleTag) = 0;
	virtual void AddRules(FGameplayTagContainer InRulesContainer) = 0;


	/** Add the event to the queue, so it can play again */
	virtual void AddEventToQueue(FCADialogueEvent Event) = 0;

	/** Check all events and clear them if they have expired */
	virtual void ClearExpiredEventsInQueue() = 0;

private:
	/** Internally spawn and register the instance class */
	virtual void RegisterInstance() = 0;

	/** Deregister the instance and clear its pointer */
	virtual void DeregisterInstance() = 0;
};