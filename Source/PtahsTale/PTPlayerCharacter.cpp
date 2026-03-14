#include "PTPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PTBuffComponent.h"
#include "PTCombatComponent.h"
#include "PTInventoryComponent.h"
#include "PTStatsComponent.h"

APTPlayerCharacter::APTPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    bUseControllerRotationYaw = true;
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->MaxWalkSpeed = 350.f;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 280.f;
    CameraBoom->bUsePawnControlRotation = true;
    CameraBoom->SetRelativeLocation(FVector(0.f, 70.f, 70.f));

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    StatsComponent = CreateDefaultSubobject<UPTStatsComponent>(TEXT("StatsComponent"));
    InventoryComponent = CreateDefaultSubobject<UPTInventoryComponent>(TEXT("InventoryComponent"));
    BuffComponent = CreateDefaultSubobject<UPTBuffComponent>(TEXT("BuffComponent"));
    CombatComponent = CreateDefaultSubobject<UPTCombatComponent>(TEXT("CombatComponent"));
}

void APTPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APTPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APTPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APTPlayerCharacter::Turn);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APTPlayerCharacter::LookUp);

    PlayerInputComponent->BindAction(TEXT("Dodge"), IE_Pressed, this, &APTPlayerCharacter::Dodge);
}

void APTPlayerCharacter::MoveForward(float Value)
{
    if (Controller && Value != 0.f)
    {
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void APTPlayerCharacter::MoveRight(float Value)
{
    if (Controller && Value != 0.f)
    {
        AddMovementInput(GetActorRightVector(), Value);
    }
}

void APTPlayerCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void APTPlayerCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void APTPlayerCharacter::Dodge()
{
    if (CombatComponent && CombatComponent->TryDodge())
    {
        LaunchCharacter(GetActorForwardVector() * 600.f, true, false);
    }
}
