#include "PTBuffComponent.h"

#include "PTStatsComponent.h"

UPTBuffComponent::UPTBuffComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UPTBuffComponent::AddBuff(const FPTBuffSpec& BuffSpec)
{
    FPTActiveBuff Buff;
    Buff.Spec = BuffSpec;
    Buff.TimeRemaining = BuffSpec.Duration;
    ActiveBuffs.Add(Buff);
}

void UPTBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!StatsComponent)
    {
        StatsComponent = GetOwner()->FindComponentByClass<UPTStatsComponent>();
    }

    if (!StatsComponent)
    {
        return;
    }

    for (int32 i = ActiveBuffs.Num() - 1; i >= 0; --i)
    {
        FPTActiveBuff& Buff = ActiveBuffs[i];
        Buff.TimeRemaining -= DeltaTime;

        if (Buff.Spec.HealthRegenPerSecond != 0.f)
        {
            StatsComponent->Heal(Buff.Spec.HealthRegenPerSecond * DeltaTime);
        }

        if (Buff.Spec.StaminaRegenPerSecond != 0.f)
        {
            StatsComponent->RestoreStamina(Buff.Spec.StaminaRegenPerSecond * DeltaTime);
        }

        if (Buff.TimeRemaining <= 0.f)
        {
            ActiveBuffs.RemoveAt(i);
        }
    }
}
