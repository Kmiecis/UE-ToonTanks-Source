#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"

#include "PawnTank.h"

APawnTurret::APawnTurret()
{
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerTank != nullptr && GetDistanceToPlayer() <= FireRange)
	{
		auto PlayerLocation = PlayerTank->GetActorLocation();
		RotateTurretTowards(PlayerLocation);
	}
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	auto& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	auto* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	PlayerTank = Cast<APawnTank>(PlayerPawn);
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
}

void APawnTurret::CheckFireCondition()
{
	if (PlayerTank != nullptr && GetDistanceToPlayer() <= FireRange)
	{
		Fire();
	}
}

float APawnTurret::GetDistanceToPlayer()
{
	if (PlayerTank != nullptr)
	{
		return FVector::Dist(PlayerTank->GetActorLocation(), GetActorLocation());
	}
	return 0.0f;
}
