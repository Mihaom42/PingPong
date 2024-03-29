// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PingPongController.generated.h"

/**
 * 
 */
UCLASS()
class PINGPONG_API APingPongController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	void Move(float Amount);
};
