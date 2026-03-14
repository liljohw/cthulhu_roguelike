#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PTPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UPTStatsComponent;
class UPTInventoryComponent;
class UPTBuffComponent;
class UPTCombatComponent;

UCLASS()
class THE_PTAH_TALE_API APTPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    APTPlayerCharacter();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG")
    TObjectPtr<UPTStatsComponent> StatsComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG")
    TObjectPtr<UPTInventoryComponent> InventoryComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG")
    TObjectPtr<UPTBuffComponent> BuffComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "RPG")
    TObjectPtr<UPTCombatComponent> CombatComponent;

private:
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void Dodge();
};
