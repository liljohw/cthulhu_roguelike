#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGTypes.h"
#include "PTBuffComponent.generated.h"

class UPTStatsComponent;

USTRUCT()
struct FPTActiveBuff
{
    GENERATED_BODY()

    UPROPERTY()
    FPTBuffSpec Spec;

    UPROPERTY()
    float TimeRemaining = 0.f;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THE_PTAH_TALE_API UPTBuffComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPTBuffComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Buffs")
    void AddBuff(const FPTBuffSpec& BuffSpec);

private:
    UPROPERTY()
    TArray<FPTActiveBuff> ActiveBuffs;

    UPROPERTY()
    TObjectPtr<UPTStatsComponent> StatsComponent;
};
