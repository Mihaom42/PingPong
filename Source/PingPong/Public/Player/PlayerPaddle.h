// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPaddle.generated.h"

UCLASS()
class APlayerPaddle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPaddle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector PaddleVelocity;

	UFUNCTION(Server, Reliable)
	void Server_SendPlayerTransformToServer(FTransform NewTransform);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, Replicated)
	class UStaticMeshComponent* PaddleMesh;

	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly)
	class UBoxComponent* BoxComponent;

private:
	UPROPERTY(ReplicatedUsing = OnRep_PaddleTransform)
	FTransform PaddleTransform;

	UFUNCTION()
	void OnRep_PaddleTransform();
};
