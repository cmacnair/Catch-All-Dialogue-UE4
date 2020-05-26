#pragma once

#include "CoreMinimal.h"
#include <Engine/DeveloperSettings.h>

#include "CADialogueDeveloperSettings.generated.h"

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "CADialogue Developer Settings"))
class UCADialogueDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	/** @todo - find a better way of defining hierarchy */

	/** Map instance subclass to a numerical priority value 0 = lowest, 100 = highest */
	UPROPERTY(config, EditAnywhere, Category = Commentator)
	TMap<FGameplayTag, int> InstancePriorityDefinitionInMap;
		
	static UCADialogueDeveloperSettings* Get() { return CastChecked<UCADialogueDeveloperSettings>(UCADialogueDeveloperSettings::StaticClass()->GetDefaultObject()); };
};