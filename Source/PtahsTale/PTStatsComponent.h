#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPGTypes.h"
#include "PTStatsComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THE_PTAH_TALE_API UPTStatsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UPTStatsComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    FPTCharacterStats Stats;

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void ApplyDamage(float Amount, EPTDamageType DamageType);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void Heal(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    bool ConsumeStamina(float Amount);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void RestoreStamina(float Amount);
};
