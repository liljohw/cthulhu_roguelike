#include "PTInventoryComponent.h"

UPTInventoryComponent::UPTInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

float UPTInventoryComponent::GetCurrentWeight() const
{
    float Total = 0.f;
    for (const FPTInventoryEntry& Entry : Items)
    {
        Total += Entry.Data.UnitWeight * Entry.Quantity;
    }
    return Total;
}

float UPTInventoryComponent::GetMaxWeight() const
{
    return BaseCarryWeight + BackpackBonusWeight;
}

bool UPTInventoryComponent::AddItem(const FPTItemData& ItemData, int32 Quantity)
{
    if (Quantity <= 0)
    {
        return false;
    }

    const int32 MaxSlots = GridWidth * GridHeight;
    if (Items.Num() >= MaxSlots)
    {
        return false;
    }

    const float NewWeight = GetCurrentWeight() + ItemData.UnitWeight * Quantity;
    if (NewWeight > GetMaxWeight())
    {
        return false;
    }

    if (FPTInventoryEntry* Existing = FindEntry(ItemData.ItemId))
    {
        if (Existing->Quantity + Quantity <= Existing->Data.MaxStack)
        {
            Existing->Quantity += Quantity;
            return true;
        }
    }

    FPTInventoryEntry NewEntry;
    NewEntry.Data = ItemData;
    NewEntry.Quantity = Quantity;
    Items.Add(NewEntry);
    return true;
}

bool UPTInventoryComponent::ConsumeItem(FName ItemId, int32 Quantity)
{
    if (FPTInventoryEntry* Entry = FindEntry(ItemId))
    {
        if (Entry->Quantity < Quantity)
        {
            return false;
        }

        Entry->Quantity -= Quantity;
        if (Entry->Quantity <= 0)
        {
            Items.RemoveAll([&ItemId](const FPTInventoryEntry& E) { return E.Data.ItemId == ItemId; });
        }
        return true;
    }

    return false;
}

bool UPTInventoryComponent::EquipItem(FName ItemId)
{
    FPTInventoryEntry* Entry = FindEntry(ItemId);
    if (!Entry || Entry->Data.ItemType != EPTItemType::Equipment)
    {
        return false;
    }

    const EPTEqSlot Slot = Entry->Data.EquipSlot;
    if (Slot == EPTEqSlot::None)
    {
        return false;
    }

    Equipped.Add(Slot, *Entry);

    if (Slot == EPTEqSlot::Backpack)
    {
        BackpackBonusWeight = Entry->Data.BackpackBonusWeight;
    }

    return true;
}

FPTInventoryEntry* UPTInventoryComponent::FindEntry(FName ItemId)
{
    return Items.FindByPredicate([&ItemId](const FPTInventoryEntry& Entry)
    {
        return Entry.Data.ItemId == ItemId;
    });
}
