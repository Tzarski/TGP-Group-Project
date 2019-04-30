// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSprite.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "PlayerChar.h"
#include "newastar.h"
#include "Sound.h"
#include "ItemsManager.h"
#include "Enemy_Base.generated.h"


UCLASS()
class MYPROJECT_API AEnemy_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<AActor*> _foundCharacter;
	class APlayerChar * _pPlayer;
	class Anewastar * _pPathfinder;
	bool dead = false;
	int minus = 1;

	class AItemsManager* itemsManager;

	int randomID = FMath::FRandRange(1, 3);
	int randomKey = FMath::FRandRange(0, 100);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Hit();
	virtual void Pathfinder();
	virtual void Move();
	virtual void SetSprites();
	//virtual void Attack();

	float _health, _range, _damage, _speed;
	bool moved, block, attacking;
	int ticks = 0, spriteSelected;
	class UPaperSpriteComponent* enemySprite;
	USound* soundEffect, *loopSoundEffect;
	UPaperSprite* papersprite[12];
};
