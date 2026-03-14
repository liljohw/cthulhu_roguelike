#include "Combat/HealthComponent.h"
#include "GameFramework/Actor.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void UHealthComponent::TakeDamage(float DamageAmount)
{
	if (bIsDead || DamageAmount <= 0.0f)
		return;

	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);

	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth, DamageAmount);

	if (CurrentHealth <= 0.0f)
	{
		Die();
	}
}

void UHealthComponent::Heal(float HealAmount)
{
	if (bIsDead || HealAmount <= 0.0f)
		return;

	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth, -HealAmount);
}

float UHealthComponent::GetHealthPercent() const
{
	return MaxHealth > 0.0f ? CurrentHealth / MaxHealth : 0.0f;
}

void UHealthComponent::Die()
{
	bIsDead = true;
	OnDeath.Broadcast();

	// Optionally destroy the actor after a delay
	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->SetActorEnableCollision(false);
		// You can add a timer to destroy the actor if needed
	}
}
