// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Enemy_SplitterChild.generated.h"

UCLASS()
class MYPROJECT_API AEnemy_SplitterChild : public AEnemy_Base
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AEnemy_SplitterChild();

protected:
	float randomX = 0.0f, randomZ = 0.0f, changeSprite = 1;
	// Called when the game starts or when spawned


public:
	void LoadPaperSprites();
	void SetSprites();
	void Move();
	void Attack();
	void Damaged();
};
