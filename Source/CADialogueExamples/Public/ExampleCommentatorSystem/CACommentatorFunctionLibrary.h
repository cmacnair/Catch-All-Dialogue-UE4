// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

#include <GameplayTagContainer.h>
#include <Engine/DeveloperSettings.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include "CADialogueEvent.h"

#include "CACommentatorFunctionLibrary.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Commentator Dialogue Developer Settings"))
class UCACommentatorDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/** Tag to identify the Commentator System Instance */
	UPROPERTY(config, EditAnywhere, Category = Commentator)
	FGameplayTag CommentatorSystemTag;

	static UCACommentatorDeveloperSettings* Get() { return CastChecked<UCACommentatorDeveloperSettings>(UCACommentatorDeveloperSettings::StaticClass()->GetDefaultObject()); }
};


/** Game systems API for sending events to the commentator system */
UCLASS(BlueprintType)
class UCACommentatorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "CADialogue")
	static void SendCommentatorEventByTags(FGameplayTag Event, FGameplayTag Speaker, class UObject* Caller);

	UFUNCTION(BlueprintCallable, Category = "CADialogue")
	static void SendCommentatorEvent(FCADialogueEvent Event, class UObject* Caller);
};