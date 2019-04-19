// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Enemy_Tough.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AEnemy_Tough : public AEnemy_Base
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AEnemy_Tough();

protected:
	// Called when the game starts or when spawned


public:
	void LoadPaperSprites();
	void Move();
	void Attack();
	void Damaged();
};
