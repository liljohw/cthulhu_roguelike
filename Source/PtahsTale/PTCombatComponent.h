#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGTypes.h"
#include "PTCombatComponent.generated.h"

class UPTStatsComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THE_PTAH_TALE_API UPTCombatComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPTCombatComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    float MaxActionGauge = 100.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    float CurrentActionGauge = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    float ActionGaugeRegenRate = 30.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    float DodgeStaminaCost = 20.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    float DodgeCooldown = 0.5f;

    UFUNCTION(BlueprintCallable, Category = "Combat")
    bool TryExecuteSkill(const FPTSkillData& SkillData, AActor* Target);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    bool TryDodge();

private:
    UPROPERTY()
    TObjectPtr<UPTStatsComponent> StatsComponent;

    float DodgeCooldownRemaining = 0.f;

    bool RollPercentile(int32 Chance) const;
};
