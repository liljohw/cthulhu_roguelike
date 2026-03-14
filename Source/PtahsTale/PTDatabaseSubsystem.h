#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RPGTypes.h"
#include "PTDatabaseSubsystem.generated.h"

UCLASS()
class THE_PTAH_TALE_API UPTDatabaseSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    UPROPERTY(BlueprintReadOnly, Category = "Database")
    TMap<FName, FPTItemData> ItemDatabase;

    UPROPERTY(BlueprintReadOnly, Category = "Database")
    TMap<FName, FPTSkillData> SkillDatabase;

    UPROPERTY(BlueprintReadOnly, Category = "Database")
    TMap<FName, FPTBuffSpec> BuffDatabase;
};
