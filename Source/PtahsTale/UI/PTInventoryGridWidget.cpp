#include "UI/PTInventoryGridWidget.h"

#include "PTInventoryComponent.h"

void UPTInventoryGridWidget::InitializeFromInventory(UPTInventoryComponent* InInventory)
{
    Inventory = InInventory;
}
