// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

#include "CAEmoteTypes.generated.h"


/** Priorities (in order) for the emote system */
UENUM()
enum class ECAEmotePriority
{
	Off,
	Grunt,
	EffortWeak,
	EffortStrong,
	Pain,
};