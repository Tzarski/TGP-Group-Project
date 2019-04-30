// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Runtime/Core/Public/Misc/Paths.h"
#include "GameFramework/Actor.h"
#include "Globals.h"
#include "Kismet/GameplayStatics.h"
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
	ASpawnRoom(const FObjectInitializer& PCIP);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int CurrentRoom = 0;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool LoadRoomFromFile(FString RoomName);
	void SortLayers();
	void SpawnLayers(int dir);
	void SpawnRoom(int i);
	void PrintTwoInt(int i, int b);

	AGlobals* GlobVars;
	FString SavedName = "";
	TArray<int> CurrentLevels;
	TArray<AActor*> Spawnedworld;
	TArray<FmyLayer> MyLayers;
	class USound* sound, *backgroundMusic;
	USoundBase* musicBoss;
	class UPaperSpriteComponent* FloorSprite;
};
