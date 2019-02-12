// Fill out your copyright notice in the Description page of Project Settings.

#include "Protagonist.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
AProtagonist::AProtagonist()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CharacterMesh(TEXT("/Game/Geometry/Meshes/1M_Cube.1M_Cube"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> CharacterMaterial(TEXT("/Game/Geometry/Meshes/CubeMaterial.CubeMaterial"));

	character = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("character"));
	character->SetStaticMesh(CharacterMesh.Object);
	character->SetMaterial(0, CharacterMaterial.Object);
	RootComponent = character;
	

	collision = CreateDefaultSubobject<UBoxComponent>(TEXT("collision"));
	collision->SetBoxExtent(FVector(10.0f, 0.0f, 10.0f));
	collision->SetRelativeLocation(FVector(0.f, 0.f, 0.f));


}

// Called when the game starts or when spawned
void AProtagonist::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProtagonist::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AProtagonist::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AProtagonist::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AProtagonist::MoveRight);

}

void  AProtagonist::MoveRight(float scale)
{
	if (scale != 0.0f)
	{
		const FVector Direction = FVector(0.f, 10.0f * scale,0.f);
		character->AddWorldOffset(Direction);
	}	
}

void  AProtagonist::MoveForward(float scale)
{
	if (scale != 0.0f)
	{
		const FVector Direction = FVector(10.0f * scale, 0.f, 0.f);
		character->AddWorldOffset(Direction);
	}
}

