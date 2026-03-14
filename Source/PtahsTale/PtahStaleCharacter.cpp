#include "PtahStaleCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Combat/HealthComponent.h"
#include "Combat/Projectile.h"
#include "Kismet/GameplayStatics.h"

APtahStaleCharacter::APtahStaleCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Standard third-person capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	// Rotate character to movement direction; camera rotates independently
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;
	bUseControllerRotationRoll  = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;

	// Spring arm (camera boom)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	// Follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Create CoC subsystem objects
	CharacterStats = CreateDefaultSubobject<UCoCCharacterStats>(TEXT("CharacterStats"));
	SanitySystem   = CreateDefaultSubobject<USanitySystem>(TEXT("SanitySystem"));
	SkillSystem    = CreateDefaultSubobject<USkillSystem>(TEXT("SkillSystem"));

	// Create Health Component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void APtahStaleCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Register Enhanced Input mapping context
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Sync sanity max with starting POW
	SyncSanityWithPow();

	// Sync skill values that derive from characteristics (Dodge = DEX/2, Language Own = EDU)
	if (SkillSystem && CharacterStats)
	{
		SkillSystem->SyncDerivedSkillsFromCharacteristics(
			CharacterStats->Characteristics.Dexterity,
			CharacterStats->Characteristics.Education
		);
	}
}

void APtahStaleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APtahStaleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(JumpAction,  ETriggerEvent::Started,   this, &ACharacter::Jump);
		EnhancedInput->BindAction(JumpAction,  ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInput->BindAction(MoveAction,  ETriggerEvent::Triggered, this, &APtahStaleCharacter::Move);
		EnhancedInput->BindAction(LookAction,  ETriggerEvent::Triggered, this, &APtahStaleCharacter::Look);
		EnhancedInput->BindAction(ShootAction, ETriggerEvent::Triggered, this, &APtahStaleCharacter::Shoot);
		EnhancedInput->BindAction(SprintAction, ETriggerEvent::Started,  this, &APtahStaleCharacter::StartSprint);
		EnhancedInput->BindAction(SprintAction, ETriggerEvent::Completed, this, &APtahStaleCharacter::StopSprint);
	}
}

void APtahStaleCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDir   = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDir, MovementVector.Y);
		AddMovementInput(RightDir,   MovementVector.X);
	}
}

void APtahStaleCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APtahStaleCharacter::SyncSanityWithPow()
{
	if (CharacterStats && SanitySystem)
	{
		SanitySystem->CurrentSanity = CharacterStats->Characteristics.Power;
		SanitySystem->RecalculateMaxSanity();
	}
}

void APtahStaleCharacter::Shoot()
{
	// Check fire rate
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastFireTime < FireRate)
		return;

	LastFireTime = CurrentTime;

	// Spawn projectile
	if (ProjectileClass)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		FVector MuzzleLocation = CameraLocation + CameraRotation.RotateVector(FVector(100.0f, 0.0f, 0.0f));

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		GetWorld()->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, CameraRotation, SpawnParams);
	}
}

void APtahStaleCharacter::StartSprint()
{
	bIsSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void APtahStaleCharacter::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

