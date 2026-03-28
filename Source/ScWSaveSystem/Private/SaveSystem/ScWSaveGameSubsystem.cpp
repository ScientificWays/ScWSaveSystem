// Scientific Ways

#include "SaveSystem/ScWSaveGameSubsystem.h"

#include "Utils/ScWUtils.h"

#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWSaveGameSubsystem)

//~ Begin Initialize
UScWSaveGameSubsystem::UScWSaveGameSubsystem()
{
}

UScWSaveGameSubsystem* UScWSaveGameSubsystem::Get(const UObject* InWCO)
{
	UGameInstance* const GameInstance = UGameplayStatics::GetGameInstance(InWCO);
	ensureReturn(GameInstance, nullptr);
	return GameInstance->GetSubsystem<UScWSaveGameSubsystem>();
}
//~ End Initialize
