#include "PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerEnabled(bool IsPlayerEnabled)
{
	if (IsPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = IsPlayerEnabled;
}
