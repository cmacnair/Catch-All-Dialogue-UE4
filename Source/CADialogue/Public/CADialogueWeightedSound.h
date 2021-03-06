// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

#include "CADialogueWeightedSound.generated.h"


// @todo add parsing from csv to weighted sound
// @todo - add previous count until next play

/**
* Dialogue weighted sound data
* Maps a sound to a weighting
*/
USTRUCT(BlueprintType)
struct CADIALOGUE_API FCADialogueWeightedSound
{
	GENERATED_BODY()

public:
	FCADialogueWeightedSound()
		: Sound(nullptr)
		, Weighting(100)
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CADialogue")
	class USoundBase* Sound;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CADialogue", meta=(UIMin = 0, UIMax = 100))
	int32 Weighting;

	// @todo add additional effects
};