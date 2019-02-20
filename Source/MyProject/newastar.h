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
#include "Runtime/Core/Public/Misc/DateTime.h"
#include "PlayerChar.h"
#include "Enemy.h" 
#include "newastar.generated.h"

USTRUCT()
struct FASNode
{

	GENERATED_BODY()
	int MyNumber;
	int LastNumber;
	bool isClosed;
	FVector position;
	bool start;
	bool end;
	FASNode()
	{
		start = false;
		end = false;
		MyNumber = 0;
		LastNumber = 0;
		isClosed = false;
		position = FVector(0, 0, 0);
	}
	FASNode(int X, int Y, int N)
	{
		MyNumber = N;
		LastNumber = 0;
		isClosed = false;
		position = FVector(X, 0, Y);
		start = false;
		end = false;
	}

	bool operator== (const FASNode& other) const {
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
UCLASS()
class MYPROJECT_API Anewastar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Anewastar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void MapWorld();
	void FindClosestToSandE();
	void FindNeighbours();
	void FindBestNeighbour();
	void Start();

public:	
	// Called every frame
	FTimerHandle    handle;
	virtual void Tick(float DeltaTime) override;
	TArray<FASNode> nodes;
	class APlayerChar * player;
	class AEnemy * enemy;
	int current;
	bool pathfound = false;

	int end = 0;
	int start = 0;
	TArray<int> neighbours;
};
