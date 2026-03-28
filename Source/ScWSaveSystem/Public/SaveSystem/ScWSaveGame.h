// Scientific Ways

#pragma once

#include "ScWSaveSystem.h"

#include "GameFramework/SaveGame.h"

#include "ScWSaveGame.generated.h"

#define MODULE_API SCWSAVESYSTEM_API

/**
 *	Stores the active save payload for the save system and exposes typed key-value accessors.
 *	It also provides Blueprint lifecycle hooks for save, load, and reset events.
 */
UCLASS(MinimalAPI, Blueprintable, BlueprintType, meta = (DisplayName = "[ScW] Save Game"))
class UScWSaveGame : public USaveGame
{
	GENERATED_BODY()

//~ Begin Initialize
public:

	UScWSaveGame(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());
//~ End Initialize

//~ Begin ScW SaveGame System
public:

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, BlueprintPure, meta = (WorldContext = "InWCO"))
	static MODULE_API const FString& GetCurrentSaveGameDataSlot(const UObject* InWCO);

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, BlueprintPure, meta = (WorldContext = "InWCO"))
	static MODULE_API UScWSaveGame* GetCurrentSaveGameDataObject(const UObject* InWCO);

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, meta = (WorldContext = "InWCO"))
	static MODULE_API void SaveCurrentSaveGameDataToCurrentSlot(const UObject* InWCO);

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, meta = (WorldContext = "InWCO", AutoCreateRefTerm = "InSlot"))
	static MODULE_API void LoadCurrentSaveGameDataFromSlot(const UObject* InWCO, TSubclassOf<UScWSaveGame> InSaveGameClass, const FString& InSlot, int32 InUserIndex);

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, meta = (WorldContext = "InWCO"))
	static MODULE_API void ResetCurrentSaveGameData(const UObject* InWCO, bool bInSaveEmptySlot = true);

public:

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, meta = (WorldContext = "InWCO", AutoCreateRefTerm = "InKey", KeyWords = "GetBoolSave, GetSaveDataBool"))
	static MODULE_API bool GetCurrentSaveGameDataBool(const UObject* InWCO, const FString& InKey, bool bInDefaultValue);

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, meta = (WorldContext = "InWCO", AutoCreateRefTerm = "InKey", KeyWords = "GetIntegerSave, GetSaveDataInteger"))
	static MODULE_API int32 GetCurrentSaveGameDataInteger(const UObject* InWCO, const FString& InKey, int32 InDefaultValue);

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, meta = (WorldContext = "InWCO", AutoCreateRefTerm = "InKey, InDefaultValue", KeyWords = "GetFloatSave, GetSaveDataFloat"))
	static MODULE_API float GetCurrentSaveGameDataFloat(const UObject* InWCO, const FString& InKey, float InDefaultValue);

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, meta = (WorldContext = "InWCO", AutoCreateRefTerm = "InKey, InDefaultValue", KeyWords = "GetVectorSave, GetSaveDataVector"))
	static MODULE_API FVector GetCurrentSaveGameDataVector(const UObject* InWCO, const FString& InKey, FVector InDefaultValue);

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, meta = (WorldContext = "InWCO", AutoCreateRefTerm = "InKey, InDefaultValue", KeyWords = "GetStringSave, GetSaveDataString"))
	static MODULE_API FString GetCurrentSaveGameDataString(const UObject* InWCO, const FString& InKey, FString InDefaultValue);

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, meta = (WorldContext = "InWCO", AutoCreateRefTerm = "InKey", KeyWords = "SaveBoolKey, SetSaveDataBool"))
	static MODULE_API void SetCurrentSaveGameDataBool(const UObject* InWCO, const FString& InKey, bool bInValue);

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, meta = (WorldContext = "InWCO", AutoCreateRefTerm = "InKey, InValue", KeyWords = "SaveIntegerKey, SetSaveDataInteger"))
	static MODULE_API void SetCurrentSaveGameDataInteger(const UObject* InWCO, const FString& InKey, int32 InValue);

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, meta = (WorldContext = "InWCO", AutoCreateRefTerm = "InKey, InValue", KeyWords = "SaveFloatKey, SetSaveDataFloat"))
	static MODULE_API void SetCurrentSaveGameDataFloat(const UObject* InWCO, const FString& InKey, float InValue);

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, meta = (WorldContext = "InWCO", AutoCreateRefTerm = "InKey, InValue", KeyWords = "SaveVectorKey, SetSaveDataVector"))
	static MODULE_API void SetCurrentSaveGameDataVector(const UObject* InWCO, const FString& InKey, FVector InValue);

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, meta = (WorldContext = "InWCO", AutoCreateRefTerm = "InKey, InValue", KeyWords = "SaveStringKey, SetSaveDataString"))
	static MODULE_API void SetCurrentSaveGameDataString(const UObject* InWCO, const FString& InKey, FString InValue);

	UFUNCTION(Category = "ScW SaveGame System", BlueprintCallable, meta = (WorldContext = "InWCO", AutoCreateRefTerm = "InKey", KeyWords = "GetBoolSave, GetSaveDataBool", ExpandBoolAsExecs = "ReturnValue"))
	static bool SwitchCurrentSaveGameDataBool(const UObject* InWCO, const FString& InKey, bool bInDefaultValue) { return GetCurrentSaveGameDataBool(InWCO, InKey, bInDefaultValue); }
//~ End ScW SaveGame System

//~ Begin Blueprints
protected:

	UFUNCTION(Category = "Blueprints", BlueprintImplementableEvent, BlueprintCallable, meta = (WorldContext = "InWCO", DisplayName = "Pre SaveGame Save"))
	void BP_PreSaveGameSave(const UObject* InWCO) const;

	UFUNCTION(Category = "Blueprints", BlueprintImplementableEvent, BlueprintCallable, meta = (WorldContext = "InWCO", DisplayName = "Post SaveGame Load"))
	void BP_PostSaveGameLoad(const UObject* InWCO) const;

	UFUNCTION(Category = "Blueprints", BlueprintImplementableEvent, BlueprintCallable, meta = (WorldContext = "InWCO", DisplayName = "Reset SaveGame Data"))
	void BP_ResetSaveGameData(const UObject* InWCO) const;
//~ End Blueprints

//~ Begin Data
protected:

	UPROPERTY(Category = "Data", EditAnywhere, BlueprintReadWrite)
	TMap<FString, bool> BoolKeys;

	UPROPERTY(Category = "Data", EditAnywhere, BlueprintReadWrite)
	TMap<FString, int32> IntegerKeys;

	UPROPERTY(Category = "Data", EditAnywhere, BlueprintReadWrite)
	TMap<FString, float> FloatKeys;

	UPROPERTY(Category = "Data", EditAnywhere, BlueprintReadWrite)
	TMap<FString, FVector> VectorKeys;

	UPROPERTY(Category = "Data", EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> StringKeys;
//~ End Data
};

#undef MODULE_API
