// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

#include <GameplayTagContainer.h>
#include <Engine/DeveloperSettings.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include "CADialogueEvent.h"

#include "CAEmoteFunctionLibrary.generated.h"

/**
* Global settings for the emote system
* Could implement global features and settings if any specific contexts arise
*/
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Commentator Dialogue Developer Settings"))
class UCAEmoteDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/** Tag to identify the Commentator System Instance */
	UPROPERTY(config, EditAnywhere, Category = Emote)
	FGameplayTag EmoteSystemTag;

	static UCAEmoteDeveloperSettings* Get() { return CastChecked<UCAEmoteDeveloperSettings>(UCAEmoteDeveloperSettings::StaticClass()->GetDefaultObject()); }
};


/** Game systems API for sending events to the emote system */
UCLASS(BlueprintType)
class UCAEmoteFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Send an emote command for the given player */
	UFUNCTION(BlueprintCallable, Category = "CADialogue")
	static void PlayEmoteForPlayer(FGameplayTag EmoteTag, FGameplayTag PlayerTag, class UObject* Caller);
};