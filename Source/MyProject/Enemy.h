// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSprite.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "PlayerChar.h"
#include "newastar.h"
#include "GenericPlatformMath.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Enemy.generated.h"


UCLASS()
class MYPROJECT_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy(const FObjectInitializer& PCIP);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<AActor*> foundCharacter;
	class APlayerChar * player;
	class Anewastar * pathfinder;
	bool dead = false;
	int minus = 1;

	class AItemsManager* itemsManager;

	int randomID = FMath::FRandRange(1,3);
	int randomKey = FMath::FRandRange(0, 100);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Hit();
	bool moved;
	int ticks = 0;
	class UPaperSpriteComponent* defaultsprite;
};
