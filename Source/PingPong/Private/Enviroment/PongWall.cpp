// Fill out your copyright notice in the Description page of Project Settings.


#include "Enviroment/PongWall.h"
#include "Components/BoxComponent.h"

// Sets default values
APongWall::APongWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxComponent->SetupAttachment(StaticMeshComponent);
	//BoxComponent->SetBoxExtent(FVector(100.f, 2500.f, 100.f));
	BoxComponent->SetCollisionProfileName("PhysicsActor");
}

// Called when the game starts or when spawned
void APongWall::BeginPlay()
{
	Super::BeginPlay();
	
}

