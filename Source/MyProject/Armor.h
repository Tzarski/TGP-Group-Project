// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <EngineGlobals.h>

#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSprite.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h"
#include "Armor.generated.h"

UCLASS()
class MYPROJECT_API AArmor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArmor(const FObjectInitializer& PCIP);
	void SetArmorID(int id);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UPaperSpriteComponent* ArmorComponent;
	class UPaperSpriteComponent* TempComp1;
	class UPaperSpriteComponent* TempComp2;
	
};
