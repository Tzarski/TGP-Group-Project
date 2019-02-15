// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineGlobals.h>
#include "DrawDebugHelpers.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "AStar.generated.h"



USTRUCT()
struct FNodes
{
	GENERATED_BODY()
	FVector position;
	FVector lastposition;
	int lastpos;
	struct FNodes()
	{
		position = FVector(1, 1, 1);
		lastposition = FVector(1, 1, 1);
		lastpos = 0;

	}
	struct FNodes(FVector pos, FVector pos2, int last)
	{
		position = pos;
		lastposition = pos2;
		lastpos = last;
	}
};

UCLASS()
class MYPROJECT_API AAStar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAStar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void TestSquare(float x, float y, float z);
	TArray<FVector> neighbours;
	TArray<FNodes> allpossible;
	TArray<FVector> CanWalkList;
	class APlayerChar * player;
	class AEnemy * enemy;
};
