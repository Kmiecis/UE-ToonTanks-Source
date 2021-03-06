#include "PawnTank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APawnTank::APawnTank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(Controller);
}

bool APawnTank::GetIsPlayerAlive()
{
	return IsPlayerAlive;
}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();

	IsPlayerAlive = false;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	Rotate();
	Move();

	if (PlayerController != nullptr)
	{
		FHitResult TraceHitResult = FHitResult();
		if (PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, TraceHitResult))
		{
			FVector HitLocation = TraceHitResult.ImpactPoint;
			RotateTurretTowards(HitLocation);
		}
	}
}

void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalculateMoveInput(float Value)
{
	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	MoveDirection = FVector(Value * MoveSpeed * DeltaTime, 0.0f, 0.0f);
}

void APawnTank::CalculateRotateInput(float Value)
{
	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	float RotateAmount = Value * RotateSpeed * DeltaTime;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}
