// Scientific Ways

#include "SaveSystem/ScWSaveGameSubsystem.h"

#include "Components/TimelineComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ScWSaveGameSubsystem)

//~ Begin Initialize
UScWSaveGameSubsystem::UScWSaveGameSubsystem()
{
	
}

UScWSaveGameSubsystem* UScWSaveGameSubsystem::Get(const UObject* InWCO)
{
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(InWCO);
	ensureReturn(GameInstance, nullptr);
	return GameInstance->GetSubsystem<UScWSaveGameSubsystem>();
}
//~ End Initialize
