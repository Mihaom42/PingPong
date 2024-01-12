// Copyright Epic Games, Inc. All Rights Reserved.


#include "PingPongGameModeBase.h"
#include "Player/PlayerPaddle.h"
#include "Player/PingPongController.h"
#include "Kismet/GameplayStatics.h"

APingPongGameModeBase::APingPongGameModeBase()
{
	//DefaultPawnClass = APlayerPaddle::StaticClass();
	PlayerControllerClass = APingPongController::StaticClass();
}

void APingPongGameModeBase::StartPlay()
{
	Super::StartPlay();
}

void APingPongGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	TArray<AActor*> PawnArray;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerPaddle::StaticClass(), PawnArray);

	if (PawnArray.Num() > 0)
	{
		for (AActor* Actor : PawnArray)
		{
			APlayerPaddle* PlayerPaddle = Cast<APlayerPaddle>(Actor);

			if (PlayerPaddle && !Cast<APingPongController>(PlayerPaddle->GetController()))
			{
				NewPlayer->Possess(PlayerPaddle);
				PlayerPaddle->SetOwner(NewPlayer);
			}
		}
	}
}