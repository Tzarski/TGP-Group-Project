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
#include <utility>
#include "AStar.generated.h"
using namespace std::rel_ops;


USTRUCT()
struct FNodes
{
	GENERATED_BODY()
	FVector position;
	FVector lastposition;
	int lastpos;
	int myNumber;
	struct FNodes()
	{
		position = FVector(1, 1, 1);
		lastposition = FVector(1, 1, 1);
		lastpos = 0;
		myNumber = 0;

	}
	struct FNodes(FVector pos,  int number)
	{
		position = pos;
		lastposition = FVector(1, 1, 1);
		lastpos = 0;
		myNumber = number;
	}
	struct FNodes(FVector pos)
	{
		position = pos;
		lastposition = FVector(1, 1, 1);
		lastpos = 0;
		myNumber = 0;
	}
	struct FNodes(FVector pos, FVector pos2, int last)
	{
		position = pos;
		lastposition = pos2;
		lastpos = last;
		myNumber = 0;
	}struct FNodes(FVector pos, FVector pos2, int current, int last)
	{
		position = pos;
		lastposition = pos2;
		lastpos = last;
		myNumber = current;
	}

	bool operator== (const FNodes& other) const {
		if (position == other.position)
			return true;
		else
			return false;
	}
	bool operator== (const FVector& other) const {
		if (position == other)
			return true;
		else
			return false;
	}
};

//bool operator==(const FNodes &, const FNodes &) = default;
//bool operator!=(const FNodes &, const FNodes &) = default;

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
	bool TestSquare(float x, float y, float z,int loop);
	TArray<FNodes> neighbours;
	TArray<FNodes> allpossible;
	TArray<FNodes> basiclist;
	TArray<FNodes> CanWalkList;
	class APlayerChar * player;
	class AEnemy * enemy;
	int size ;

	
};
