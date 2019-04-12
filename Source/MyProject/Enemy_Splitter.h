// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSprite.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "PlayerChar.h"
#include "newastar.h"
#include "Enemy_Splitter.generated.h"

UCLASS()
class MYPROJECT_API AEnemy_Splitter : public AEnemy_Base
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AEnemy_Splitter(const FObjectInitializer& PCIP);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<AActor*> _foundCharacter;
	class APlayerChar * _pPlayer;
	class Anewastar * _pPathfinder;
	bool dead = false;
	int minus = 1;

public:
	// Called every frame
	void Tick(float DeltaTime) override;
	void Hit();
	//virtual void Attack();
	int _health, _range, _damage, _speed;
	void Pathfinder();
	bool moved;
	int ticks = 0;
	class UPaperSpriteComponent* enemySprite;
};
