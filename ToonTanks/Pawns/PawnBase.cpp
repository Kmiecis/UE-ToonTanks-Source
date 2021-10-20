#include "PawnBase.h"

#include "Components/CapsuleComponent.h"

APawnBase::APawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void APawnBase::RotateTurretTowards(FVector LookAtLocation)
{
	auto TurretLocation = TurretMesh->GetComponentLocation();
	auto TargetLocation = FVector(LookAtLocation.X, LookAtLocation.Y, TurretLocation.Z);
	auto TurretRotation = FVector(TargetLocation - TurretLocation).Rotation();

	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("FIRE"));
}

void APawnBase::HandleDestruction()
{
}
