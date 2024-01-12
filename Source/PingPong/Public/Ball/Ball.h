// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class PINGPONG_API ABall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABall();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "MeshComponent")
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, Category = "MeshComponent")
	class UBoxComponent* BoxComponent;

private:
	UPROPERTY(ReplicatedUsing = OnRep_BallTransform)
	FTransform BallTransform;

	UFUNCTION(Server, Reliable)
	void Server_SendBallTransformToServer(FTransform NewTransform);

	UFUNCTION()
	void OnRep_BallTransform();
};
