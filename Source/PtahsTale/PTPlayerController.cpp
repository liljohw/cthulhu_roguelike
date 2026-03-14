#include "PTPlayerController.h"

#include "PTCombatComponent.h"
#include "PTDatabaseSubsystem.h"
#include "PTPlayerCharacter.h"

APTPlayerController::APTPlayerController()
{
    bShowMouseCursor = false;
    bEnableClickEvents = false;
}

void APTPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction(TEXT("PrimaryAction"), IE_Pressed, this, &APTPlayerController::PrimaryAction);
}

void APTPlayerController::PrimaryAction()
{
    APTPlayerCharacter* Character = Cast<APTPlayerCharacter>(GetPawn());
    if (!Character || !Character->CombatComponent)
    {
        return;
    }

    UPTDatabaseSubsystem* DB = GetGameInstance() ? GetGameInstance()->GetSubsystem<UPTDatabaseSubsystem>() : nullptr;
    if (!DB)
    {
        return;
    }

    const FPTSkillData* Skill = DB->SkillDatabase.Find("firearm_attack");
    if (!Skill)
    {
        return;
    }

    FVector Start;
    FRotator ViewRot;
    GetPlayerViewPoint(Start, ViewRot);

    const FVector End = Start + ViewRot.Vector() * 1500.f;
    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(PrimaryActionTrace), true, Character);
    GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Pawn, Params);

    Character->CombatComponent->TryExecuteSkill(*Skill, Hit.GetActor());
}
