#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PTInventoryGridWidget.generated.h"

class UPTInventoryComponent;

UCLASS()
class THE_PTAH_TALE_API UPTInventoryGridWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void InitializeFromInventory(UPTInventoryComponent* InInventory);

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Inventory")
    TObjectPtr<UPTInventoryComponent> Inventory;
};
