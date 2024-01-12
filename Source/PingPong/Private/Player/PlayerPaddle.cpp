// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerPaddle.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
APlayerPaddle::APlayerPaddle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleMesh"));
	PaddleMesh->SetCollisionProfileName(FName("PhysicsActor"));

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(PaddleMesh);
	BoxComponent->SetCollisionProfileName("PhysicsActor");

	bReplicates = true;
}

// Called when the game starts or when spawned
void APlayerPaddle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PaddleVelocity = PaddleMesh->GetPhysicsLinearVelocity();
}

void APlayerPaddle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerPaddle, PaddleTransform);
}

void APlayerPaddle::Server_SendPlayerTransformToServer_Implementation(FTransform Location)
{
	PaddleTransform = Location;
}

void APlayerPaddle::OnRep_PaddleTransform()
{
	SetActorTransform(PaddleTransform);
}