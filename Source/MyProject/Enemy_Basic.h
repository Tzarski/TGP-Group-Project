// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Enemy_Basic.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AEnemy_Basic : public AEnemy_Base
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AEnemy_Basic(const FObjectInitializer& PCIP);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<AActor*> _foundCharacter;
	class Anewastar * _pPathfinder;
	class APlayerChar * _pPlayer;
	bool dead = false;
	int minus = 1;

public:
	// Called every frame
	void Tick(float DeltaTime) override;
	void Hit();
	void Pathfinder();
	//virtual void Attack();

	int _health, _range, _damage, _speed;
	bool moved;
	int ticks = 0;

	class UPaperSpriteComponent* enemySprite;
};
