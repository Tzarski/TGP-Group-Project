// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Protagonist.h"
#include "UObject/UnrealType.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> EnemyMesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> EnemyMaterial(TEXT("/Game/StarterContent/Props/Materials/M_MaterialSphere.M_MaterialSphere"));

	enemy = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("character"));
	enemy->SetStaticMesh(EnemyMesh.Object);
	enemy->SetMaterial(0, EnemyMaterial.Object);
	RootComponent = enemy;


	enemyCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("collision"));
	enemyCollision->SetBoxExtent(FVector(10.0f, 0.0f, 10.0f));
	enemyCollision->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProtagonist::StaticClass(), foundCharacter);
	for (AActor* player : foundCharacter)
	{
		protagonist = Cast<AProtagonist>(player);
	}
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector DistanceBetweenActors = (protagonist->GetActorLocation() - GetActorLocation());
	FRotator Rotation = FRotationMatrix::MakeFromX(DistanceBetweenActors).Rotator();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	enemy->AddWorldOffset(Direction);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

