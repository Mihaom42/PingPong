// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/Ball.h"
#include "Components/BoxComponent.h"
#include "Player/PlayerPaddle.h"
#include "Enviroment/PongWall.h"
#include "Components/StaticMeshComponent.h" 
#include "Net/UnrealNetwork.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->SetConstraintMode(EDOFMode::XYPlane);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionProfileName("Trigger");
	BoxComponent->SetBoxExtent(FVector(150.f, 150.f, 150.f));

	bReplicates = true;
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Server_SendBallTransformToServer(GetActorTransform());
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector::ZeroVector);
	StaticMeshComponent->SetPhysicsLinearVelocity(FVector((FMath::RandBool() ? 1.f : -1.f) * 3000.f, 
		FMath::RandRange(-300.f, 300.f), 0.f));

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABall::OnOverlap);
}

void ABall::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerPaddle* PongPlayer = Cast<APlayerPaddle>(OtherActor);

	float Speed = 10000.f;

	if (PongPlayer)
	{
		const FVector BallLinearVelocity = StaticMeshComponent->GetPhysicsLinearVelocity();
		const FVector PaddleLinearVelocity = PongPlayer->PaddleVelocity;

		const FVector NewBallLinearVelocity = FVector(Speed, BallLinearVelocity.Y, BallLinearVelocity.Z);

		StaticMeshComponent->SetPhysicsLinearVelocity(NewBallLinearVelocity);
	}

	APongWall* PongWall = Cast<APongWall>(OtherActor);
	if (PongWall)
	{
		Speed = 5000.f;

		const FVector BallLinearVelocity = StaticMeshComponent->GetPhysicsLinearVelocity();
		const FVector NewBallLinearVelocity = FVector(BallLinearVelocity.X, Speed,
			BallLinearVelocity.Z);

		StaticMeshComponent->SetPhysicsLinearVelocity(NewBallLinearVelocity);
	}

	/*APongGoal* PongGoal = Cast<APongGoal>(OtherActor);
	if (PongGoal)
	{
		Restart();
	}*/
}

void ABall::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(ABall, BallTransform);
}

void ABall::Server_SendBallTransformToServer_Implementation(FTransform NewTransform)
{
	//BallTransform = NewTransform;
}

void ABall::OnRep_BallTransform()
{
	//SetActorTransform(BallTransform);
}
