// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

#include "CADialogueDebugTypes.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(CADialogueDebugLog, Log, All);



/**
USTRUCT()
struct CADIALOGUE_API FSVRDialogueInstanceBaseSet
{
	GENERATED_BODY()
	FString	Key;

	UPROPERTY()
	TSet<class USVRDialogueInstanceBase*> Instances;
};


typedef TMap<const class UClass*, FSVRDialogueInstanceBaseSet> FSVRDialogueInstanceMap;
*/