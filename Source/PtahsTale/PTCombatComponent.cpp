#include "PTCombatComponent.h"

#include "PTStatsComponent.h"

UPTCombatComponent::UPTCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UPTCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    CurrentActionGauge = FMath::Clamp(CurrentActionGauge + ActionGaugeRegenRate * DeltaTime, 0.f, MaxActionGauge);
    DodgeCooldownRemaining = FMath::Max(0.f, DodgeCooldownRemaining - DeltaTime);

    if (!StatsComponent)
    {
        StatsComponent = GetOwner()->FindComponentByClass<UPTStatsComponent>();
    }
}

bool UPTCombatComponent::TryExecuteSkill(const FPTSkillData& SkillData, AActor* Target)
{
    if (CurrentActionGauge < SkillData.ActionCost)
    {
        return false;
    }

    CurrentActionGauge -= SkillData.ActionCost;

    if (!RollPercentile(SkillData.SuccessChance) || !Target)
    {
        return false;
    }

    if (UPTStatsComponent* TargetStats = Target->FindComponentByClass<UPTStatsComponent>())
    {
        TargetStats->ApplyDamage(SkillData.BasePower, SkillData.DamageType);
    }

    return true;
}

bool UPTCombatComponent::TryDodge()
{
    if (!StatsComponent)
    {
        return false;
    }

    if (DodgeCooldownRemaining > 0.f)
    {
        return false;
    }

    if (!StatsComponent->ConsumeStamina(DodgeStaminaCost))
    {
        return false;
    }

    DodgeCooldownRemaining = DodgeCooldown;
    return true;
}

bool UPTCombatComponent::RollPercentile(int32 Chance) const
{
    const int32 Roll = FMath::RandRange(1, 100);
    return Roll <= Chance;
}
