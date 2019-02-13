// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Runtime/Core/Public/Misc/Paths.h"
#include "GameFramework/Actor.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "SpawnRoom.generated.h"

USTRUCT()
struct FmyLayer
{
	GENERATED_BODY()

	UPROPERTY()
		int layerID;
	
		char spawn;

	FmyLayer()
	{
		layerID = 0;
		spawn = ' ';
	}
	FmyLayer(int layerid, char tospawn)
	{
		layerID = layerid;
		spawn = tospawn;
	}
};

UCLASS()
class MYPROJECT_API ASpawnRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool LoadRoomFromFile(FString RoomName);
	void SortLayers();
	void SpawnLayers();
	void SpawnRoom(int i);
	FString SavedName = "";
	TArray<AActor*> Spawnedworld;
	TArray<FmyLayer> MyLayers;
	
};
