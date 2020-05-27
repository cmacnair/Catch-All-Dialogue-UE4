// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include <Commandlets/Commandlet.h>

#include "CADialogueCommandlet.generated.h"

/**
* Commandlet for performing useful data gathering for dialogue
*
* @todo
* - usage report
* - data import
* - data validation
* - stress test
*/
UCLASS()
class UCADialogueCommandlet : public UCommandlet
{
	GENERATED_BODY()

public:
	//~ Begin UCommandlet Interface
	virtual int32 Main(const FString& Params) override;
	//~ End UCommandlet Interface

private:
	/** Report general usage stats of dialogue */
	static bool PerformUsageReport();
};

