// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Enemy_SplitterChild.h"
#include "Enemy_Splitter.generated.h"

UCLASS()
class MYPROJECT_API AEnemy_Splitter : public AEnemy_Base
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AEnemy_Splitter();

protected:
	float randomX = 0.0f, randomZ = 0.0f, changeSprite = 1;
	FActorSpawnParameters SpawnInfo;
	
public:
	TArray<AActor*> _foundCharacter;
	AGlobals* globals;
	void LoadPaperSprites();
	void SetSprites();
	void Move();
	void Attack();
	void Damaged();
	void Split();
};
