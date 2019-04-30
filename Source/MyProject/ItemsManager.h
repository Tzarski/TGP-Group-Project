// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "ItemsManager.generated.h"

UCLASS()
class MYPROJECT_API AItemsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnItems(FVector position, int id, int key);

	class ASpawnWeapon* spawnWeapon;
	class ASpawnArmor* spawnArmor;
	class ASpawnOtherItems* spawnOtherItems;
};
