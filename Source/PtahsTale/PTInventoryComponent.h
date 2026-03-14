#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGTypes.h"
#include "PTInventoryComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THE_PTAH_TALE_API UPTInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPTInventoryComponent();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    int32 GridWidth = 8;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    int32 GridHeight = 5;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
    float BaseCarryWeight = 25.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    float BackpackBonusWeight = 0.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    TArray<FPTInventoryEntry> Items;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
    TMap<EPTEqSlot, FPTInventoryEntry> Equipped;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    float GetCurrentWeight() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    float GetMaxWeight() const;

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool AddItem(const FPTItemData& ItemData, int32 Quantity);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool ConsumeItem(FName ItemId, int32 Quantity);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool EquipItem(FName ItemId);

private:
    FPTInventoryEntry* FindEntry(FName ItemId);
};
