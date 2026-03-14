#pragma once

#include "CoreMinimal.h"
#include "RPGTypes.generated.h"

UENUM(BlueprintType)
enum class EPTDamageType : uint8
{
    Physical,
    Elemental,
    Energy,
    Mental
};

UENUM(BlueprintType)
enum class EPTItemType : uint8
{
    Consumable,
    Equipment,
    Material,
    Quest
};

UENUM(BlueprintType)
enum class EPTEqSlot : uint8
{
    None,
    Head,
    Body,
    Weapon,
    OffHand,
    Backpack,
    Accessory
};

USTRUCT(BlueprintType)
struct FPTCharacterStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxHealth = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Health = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxStamina = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Stamina = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Sanity = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Strength = 50;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Dexterity = 50;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Intelligence = 50;
};

USTRUCT(BlueprintType)
struct FPTItemData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EPTItemType ItemType = EPTItemType::Material;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EPTEqSlot EquipSlot = EPTEqSlot::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float UnitWeight = 1.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStack = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BackpackBonusWeight = 0.f;
};

USTRUCT(BlueprintType)
struct FPTInventoryEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FPTItemData Data;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Quantity = 1;
};

USTRUCT(BlueprintType)
struct FPTSkillData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SkillId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText SkillName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 SuccessChance = 50;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ActionCost = 25.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BasePower = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EPTDamageType DamageType = EPTDamageType::Physical;
};

USTRUCT(BlueprintType)
struct FPTBuffSpec
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BuffId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText BuffName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Duration = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float HealthRegenPerSecond = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StaminaRegenPerSecond = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MoveSpeedMultiplier = 1.f;
};
