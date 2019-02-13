// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSprite.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h"
#include "GameFramework/Actor.h"
#include "Roof.generated.h"

UCLASS()
class MYPROJECT_API ARoof : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoof(const FObjectInitializer& PCIP);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void setSprite(int i);
	class UPaperSpriteComponent* defaultsprite;
	class UPaperSpriteComponent* sprite1;
	
	
};
