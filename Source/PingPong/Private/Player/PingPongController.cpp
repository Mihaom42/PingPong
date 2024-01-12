// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PingPongController.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Player/PlayerPaddle.h"

void APingPongController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MovePaddle", this, &APingPongController::Move);
}

void APingPongController::Move(float Amount)
{
	if (Amount == 0)
	{
		return;
	}
	
	APlayerPaddle* ControlledPawn = Cast<APlayerPaddle>(GetPawn());

	if (ControlledPawn != nullptr)
	{
		FVector CurrentLocation = ControlledPawn->GetActorLocation();
		CurrentLocation.Y += Amount * 50.F;

		ControlledPawn->SetActorLocation(CurrentLocation);

		ControlledPawn->Server_SendPlayerTransformToServer(ControlledPawn->GetTransform());
	}
}

void APingPongController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TArray<AActor*> CameraArray;
	UGameplayStatics::GetAllActorsOfClass(this, ACameraActor::StaticClass(), CameraArray);

	if (CameraArray.Num() > 0)
	{
		SetViewTargetWithBlend(CameraArray[0]);
	}
}