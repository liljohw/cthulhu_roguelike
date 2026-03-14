#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CoC/CoCCharacterStats.h"
#include "CoC/SanitySystem.h"
#include "CoC/SkillSystem.h"
#include "PtahStaleCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * APtahStaleCharacter
 *
 * The player-controlled investigator in PtahStale.
 * Owns the three core CoC subsystems: characteristics/stats, sanity, and skills.
 */
UCLASS(config = Game)
class APtahStaleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APtahStaleCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	// ── Camera ────────────────────────────────────────────────────────────

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	// ── Enhanced Input ────────────────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SprintAction;

	// ── Combat ────────────────────────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float FireRate = 0.5f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<class UHealthComponent> HealthComponent;

	// ── Movement ──────────────────────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float SprintSpeed = 800.0f;

	// ── CoC Systems ───────────────────────────────────────────────────────

	/** Core CoC characteristics and derived stats */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CoC")
	TObjectPtr<UCoCCharacterStats> CharacterStats;

	/** Sanity subsystem */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CoC")
	TObjectPtr<USanitySystem> SanitySystem;

	/** Skill subsystem */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CoC")
	TObjectPtr<USkillSystem> SkillSystem;

	// ── Helpers ───────────────────────────────────────────────────────────

	/**
	 * Synchronises the sanity system's MaxSanity with the POW characteristic.
	 * Should be called after changing POW.
	 */
	UFUNCTION(BlueprintCallable, Category = "CoC")
	void SyncSanityWithPow();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Shoot();

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartSprint();
	void StopSprint();

private:
	float LastFireTime = 0.0f;
	bool bIsSprinting = false;
};
