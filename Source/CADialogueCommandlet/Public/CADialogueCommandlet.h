// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include <Commandlets/Commandlet.h>

#include "CADialogueCommandlet.generated.h"

UCLASS()
class UCADialogueCommandlet : public UCommandlet
{
	GENERATED_BODY()

	//~ Begin UCommandlet Interface
	virtual int32 Main(const FString& Params) override;
	//~ End UCommandlet Interface
};

