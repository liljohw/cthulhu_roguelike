#include "PTStatsComponent.h"

UPTStatsComponent::UPTStatsComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UPTStatsComponent::ApplyDamage(float Amount, EPTDamageType DamageType)
{
    float Multiplier = 1.f;
    if (DamageType == EPTDamageType::Mental)
    {
        Stats.Sanity = FMath::Clamp(Stats.Sanity - Amount * 0.5f, 0.f, 100.f);
    }
    else if (DamageType == EPTDamageType::Energy)
    {
        Multiplier = 1.2f;
    }

    Stats.Health = FMath::Clamp(Stats.Health - Amount * Multiplier, 0.f, Stats.MaxHealth);
}

void UPTStatsComponent::Heal(float Amount)
{
    Stats.Health = FMath::Clamp(Stats.Health + Amount, 0.f, Stats.MaxHealth);
}

bool UPTStatsComponent::ConsumeStamina(float Amount)
{
    if (Stats.Stamina < Amount)
    {
        return false;
    }

    Stats.Stamina -= Amount;
    return true;
}

void UPTStatsComponent::RestoreStamina(float Amount)
{
    Stats.Stamina = FMath::Clamp(Stats.Stamina + Amount, 0.f, Stats.MaxStamina);
}
