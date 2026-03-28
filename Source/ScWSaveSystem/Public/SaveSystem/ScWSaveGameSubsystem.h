// Scientific Ways

#pragma once

#include "ScWSaveSystem.h"

#include "Subsystems/GameInstanceSubsystem.h"

#include "ScWSaveGameSubsystem.generated.h"

#define MODULE_API SCWSAVESYSTEM_API

class UObject;
class UScWSaveGame;

/**
 *	Tracks the currently loaded save slot, user index, and save object for the active game instance.
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
	TObjectPtr<UScWSaveGame> CurrentSaveDataObject;
//~ End Data
};

#undef MODULE_API
