// Scientific Ways

#include "SaveSystem/ScWSaveGame.h"

#include "SaveSystem/ScWSaveGameSubsystem.h"
#include "Utils/ScWUtils.h"

#include "Kismet/GameplayStatics.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWSaveGame)

//~ Begin Initialize
UScWSaveGame::UScWSaveGame(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
}
//~ End Initialize

//~ Begin ScW SaveGame System
const FString& UScWSaveGame::GetCurrentSaveGameDataSlot(const UObject* InWCO)
{
	static const FString FallbackSlot = TEXT("DefaultSaveSlot");
	UScWSaveGameSubsystem* const SaveGameSubsystem = UScWSaveGameSubsystem::Get(InWCO);
	ensureReturn(SaveGameSubsystem, FallbackSlot);
	return SaveGameSubsystem->CurrentSaveDataSlot.IsEmpty() ? FallbackSlot : SaveGameSubsystem->CurrentSaveDataSlot;
}

UScWSaveGame* UScWSaveGame::GetCurrentSaveGameDataObject(const UObject* InWCO)
{
	ensureReturn(InWCO, nullptr);
	UScWSaveGameSubsystem* const SaveGameSubsystem = UScWSaveGameSubsystem::Get(InWCO);
	ensureReturn(SaveGameSubsystem, nullptr);
	return SaveGameSubsystem->CurrentSaveDataObject;
}

void UScWSaveGame::SaveCurrentSaveGameDataToCurrentSlot(const UObject* InWCO)
{
	ensureReturn(InWCO);
	UScWSaveGameSubsystem* const SaveGameSubsystem = UScWSaveGameSubsystem::Get(InWCO);
	ensureReturn(SaveGameSubsystem);

	ensureReturn(SaveGameSubsystem->CurrentSaveDataObject);
	SaveGameSubsystem->CurrentSaveDataObject->BP_PreSaveGameSave(InWCO);

	UGameplayStatics::SaveGameToSlot(SaveGameSubsystem->CurrentSaveDataObject, SaveGameSubsystem->CurrentSaveDataSlot, SaveGameSubsystem->CurrentSaveDataUserIndex);
}

void UScWSaveGame::LoadCurrentSaveGameDataFromSlot(const UObject* InWCO, TSubclassOf<UScWSaveGame> InSaveGameClass, const FString& InSlot, int32 InUserIndex)
{
	ensureReturn(InSaveGameClass);

	ThisClass* LoadedSaveGame = nullptr;

	if (UGameplayStatics::DoesSaveGameExist(InSlot, InUserIndex))
	{
		LoadedSaveGame = Cast<ThisClass>(UGameplayStatics::LoadGameFromSlot(InSlot, InUserIndex));
	}
	else
	{
		LoadedSaveGame = Cast<ThisClass>(UGameplayStatics::CreateSaveGameObject(InSaveGameClass));
	}
	ensureReturn(LoadedSaveGame);
	ensureReturn(LoadedSaveGame->GetClass() == InSaveGameClass);

	ensureReturn(InWCO);
	UScWSaveGameSubsystem* const SaveGameSubsystem = UScWSaveGameSubsystem::Get(InWCO);
	ensureReturn(SaveGameSubsystem);
	SaveGameSubsystem->CurrentSaveDataSlot = InSlot;
	SaveGameSubsystem->CurrentSaveDataUserIndex = InUserIndex;
	SaveGameSubsystem->CurrentSaveDataObject = LoadedSaveGame;

	SaveGameSubsystem->CurrentSaveDataObject->BP_PostSaveGameLoad(InWCO);
}

void UScWSaveGame::ResetCurrentSaveGameData(const UObject* InWCO, bool bInSaveEmptySlot)
{
	ensureReturn(InWCO);
	UScWSaveGameSubsystem* const SaveGameSubsystem = UScWSaveGameSubsystem::Get(InWCO);
	ensureReturn(SaveGameSubsystem);

	ensureReturn(SaveGameSubsystem->CurrentSaveDataObject);
	SaveGameSubsystem->CurrentSaveDataObject->BoolKeys.Empty();
	SaveGameSubsystem->CurrentSaveDataObject->IntegerKeys.Empty();
	SaveGameSubsystem->CurrentSaveDataObject->FloatKeys.Empty();
	SaveGameSubsystem->CurrentSaveDataObject->VectorKeys.Empty();
	SaveGameSubsystem->CurrentSaveDataObject->StringKeys.Empty();

	SaveGameSubsystem->CurrentSaveDataObject->BP_ResetSaveGameData(InWCO);

	if (bInSaveEmptySlot)
	{
		SaveCurrentSaveGameDataToCurrentSlot(InWCO);
	}
}

#define DECLARE_GET_SET_CURRENT_SAVE_GAME_DATA(InType, InName) \
	InType UScWSaveGame::GetCurrentSaveGameData##InName(const UObject* InWCO, const FString& InKey, InType InDefaultValue) \
	{ \
		UScWSaveGame* const CurrentSaveDataObject = GetCurrentSaveGameDataObject(InWCO); \
		ensureReturn(CurrentSaveDataObject, InDefaultValue); \
		return CurrentSaveDataObject->InName##Keys.Contains(InKey) ? CurrentSaveDataObject->InName##Keys[InKey] : InDefaultValue; \
	} \
	void UScWSaveGame::SetCurrentSaveGameData##InName(const UObject* InWCO, const FString& InKey, InType InValue) \
	{ \
		UScWSaveGame* const CurrentSaveDataObject = GetCurrentSaveGameDataObject(InWCO); \
		ensureReturn(CurrentSaveDataObject); \
		CurrentSaveDataObject->InName##Keys.Add(InKey, InValue); \
	} \

DECLARE_GET_SET_CURRENT_SAVE_GAME_DATA(bool, Bool)
DECLARE_GET_SET_CURRENT_SAVE_GAME_DATA(int32, Integer)
DECLARE_GET_SET_CURRENT_SAVE_GAME_DATA(float, Float)
DECLARE_GET_SET_CURRENT_SAVE_GAME_DATA(FVector, Vector)
DECLARE_GET_SET_CURRENT_SAVE_GAME_DATA(FString, String)
//~ End ScW SaveGame System
