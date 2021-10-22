#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = DefaultHealth;
	TankGameMode = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	AActor* Actor = GetOwner();
	Actor->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage > 0.0f && Health > 0.0f)
	{
		Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);

		if (Health <= 0.0f)
		{
			if (TankGameMode != nullptr)
			{
				TankGameMode->ActorDied(GetOwner());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Health Component has no reference to TankGameMode"));
			}
		}
	}
}
