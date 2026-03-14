#include "PTDatabaseSubsystem.h"

void UPTDatabaseSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    {
        FPTItemData Backpack;
        Backpack.ItemId = "basic_backpack";
        Backpack.DisplayName = FText::FromString("Basic Backpack");
        Backpack.ItemType = EPTItemType::Equipment;
        Backpack.EquipSlot = EPTEqSlot::Backpack;
        Backpack.UnitWeight = 2.f;
        Backpack.MaxStack = 1;
        Backpack.BackpackBonusWeight = 20.f;
        ItemDatabase.Add(Backpack.ItemId, Backpack);
    }

    {
        FPTItemData Medkit;
        Medkit.ItemId = "field_medkit";
        Medkit.DisplayName = FText::FromString("Field Medkit");
        Medkit.ItemType = EPTItemType::Consumable;
        Medkit.UnitWeight = 0.5f;
        Medkit.MaxStack = 10;
        ItemDatabase.Add(Medkit.ItemId, Medkit);
    }

    {
        FPTSkillData Firearm;
        Firearm.SkillId = "firearm_attack";
        Firearm.SkillName = FText::FromString("Firearm Attack");
        Firearm.SuccessChance = 55;
        Firearm.ActionCost = 35.f;
        Firearm.BasePower = 18.f;
        Firearm.DamageType = EPTDamageType::Physical;
        SkillDatabase.Add(Firearm.SkillId, Firearm);
    }

    {
        FPTSkillData Shock;
        Shock.SkillId = "shock_burst";
        Shock.SkillName = FText::FromString("Shock Burst");
        Shock.SuccessChance = 45;
        Shock.ActionCost = 45.f;
        Shock.BasePower = 24.f;
        Shock.DamageType = EPTDamageType::Energy;
        SkillDatabase.Add(Shock.SkillId, Shock);
    }

    {
        FPTBuffSpec Adrenaline;
        Adrenaline.BuffId = "adrenaline";
        Adrenaline.BuffName = FText::FromString("Adrenaline Rush");
        Adrenaline.Duration = 8.f;
        Adrenaline.StaminaRegenPerSecond = 8.f;
        BuffDatabase.Add(Adrenaline.BuffId, Adrenaline);
    }
}
