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
	AEnemy_Splitter();

protected:
	// Called when the game starts or when spawned
	

public:
	// Called every frame
	void Damaged();
	//virtual void Attack();


};
