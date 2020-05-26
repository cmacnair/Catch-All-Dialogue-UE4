#pragma once

#include "CoreMinimal.h"

#include <UObject/Interface.h>

#include "CADialogueDebugTypes.h"

#include "CADialogueInstanceDebugInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UCADialogueInstanceDebugInterface : public UInterface
{
	GENERATED_BODY()
};

class ICADialogueInstanceDebugInterface
{
	GENERATED_BODY()

public:
	/** Make a debug report from this instance */
	virtual void MakeDebugReport() = 0;
};