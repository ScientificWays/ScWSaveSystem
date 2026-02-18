// Scientific Ways

#pragma once

#include "ScWSaveSystem.h"

#include "ScWSaveGameSubsystem.generated.h"

#define MODULE_API SCWSAVESYSTEM_API

/**
 *
 */
UCLASS(MinimalAPI, meta = (DisplayName = "[ScW] Save Game Subsystem"))
class UScWSaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

//~ Begin Initialize
public:
	UScWSaveGameSubsystem();
	static MODULE_API UScWSaveGameSubsystem* Get(const UObject* InWCO);
//~ End Initialize

//~ Begin Data
public:

	UPROPERTY(Category = "Save Data", BlueprintReadOnly)
	FString CurrentSaveDataSlot;

	UPROPERTY(Category = "Save Data", BlueprintReadOnly)
	int32 CurrentSaveDataUserIndex;

	UPROPERTY(Category = "Save Data", BlueprintReadOnly)
	TObjectPtr<class UScWSaveGame> CurrentSaveDataObject;
//~ End Data
};

#undef MODULE_API
