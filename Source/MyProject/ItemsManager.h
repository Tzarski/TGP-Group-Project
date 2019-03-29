// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemsManager.generated.h"

class ASpawnWeapon;
class ASpawnArmor;
class ASpawnOtherItems;

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

	ASpawnWeapon* spawnWeapon;
	ASpawnArmor* spawnArmor;
	ASpawnOtherItems* spawnOtherItems;
};
