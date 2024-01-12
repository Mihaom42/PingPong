// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PongWall.generated.h"

UCLASS()
class PINGPONG_API APongWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APongWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "PongWall")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "PongWall")
	class UBoxComponent* BoxComponent;
};
