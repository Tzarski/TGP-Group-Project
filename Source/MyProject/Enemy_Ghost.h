// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Base.h"
#include "Enemy_Ghost.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AEnemy_Ghost : public AEnemy_Base
{
	GENERATED_BODY()

    AEnemy_Ghost();

protected:
	//virtual void Tick(float DeltaTime) override;

public:
	void Damaged();
	
};
