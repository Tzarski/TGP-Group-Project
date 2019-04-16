// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Fireball.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AFireball : public AEnemy_Base
{
	GENERATED_BODY()

		AFireball();
protected:
	FVector Direction;
	int timer;

public:
	
	void LoadSprites();
	void Move();
	void SetSprites();
};
