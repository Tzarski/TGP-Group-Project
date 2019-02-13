// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnRoom.h"
#include "Floor.h"
#include "Roof.h"
#include "Door.h"
#include "Trap.h"
#include "Enemy.h"
// Sets default values
ASpawnRoom::ASpawnRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawnRoom::SpawnLayers()
{
	
	int row = 0;
	int columb = 1;
	FActorSpawnParameters SpawnInfo;
	const TCHAR* fuck = *SavedName;
	GEngine->AddOnScreenDebugMessage(10, 5.f, FColor::Red, FString::Printf(fuck));
	for (FmyLayer layer : MyLayers)
	{
		
		
		if (row != layer.layerID)
		{
			row = layer.layerID;
			columb = 1;
		}
		if (layer.spawn == 'f')
		{
		AFloor* one = GetWorld()->SpawnActor<AFloor>(FVector(columb * 100, 1, -row * 100), FRotator(0, 0, 0), SpawnInfo);
		Spawnedworld.Add(one);
		columb++;
		continue;
		}
		if (layer.spawn == 'w')
		{
			ARoof* one = GetWorld()->SpawnActor<ARoof>(FVector(columb * 100, 0, -row * 100), FRotator(0, 0, 0), SpawnInfo);
			Spawnedworld.Add(one);
			one->setSprite(0);
			columb++;
			continue;
		}
		if (layer.spawn == 'a')
		{
			ARoof* one = GetWorld()->SpawnActor<ARoof>(FVector(columb * 100, 0, -row * 100), FRotator(90, 0, 0), SpawnInfo);
			Spawnedworld.Add(one);
			one->setSprite(0);
			columb++;
			continue;
		}
		if (layer.spawn == 'd')
		{
			ARoof* one = GetWorld()->SpawnActor<ARoof>(FVector(columb * 100, 0, -row * 100), FRotator(-90, 0, 0), SpawnInfo);
			Spawnedworld.Add(one);
			one->setSprite(0);
			columb++;
			continue;
		}
		if (layer.spawn == 's')
		{
			ARoof* one = GetWorld()->SpawnActor<ARoof>(FVector(columb * 100, 0, -row * 100), FRotator(-180, 0, 0), SpawnInfo);
			Spawnedworld.Add(one);
			one->setSprite(0);
			columb++;
			continue;
		}
		if (layer.spawn == 'z')
		{
			ADoor* one = GetWorld()->SpawnActor<ADoor>(FVector(columb * 100, 0, -row * 100), FRotator(90, 0, 0), SpawnInfo);
			Spawnedworld.Add(one);
			columb++;
			continue;
		}
		if (layer.spawn == 'x')
		{
			ADoor* one  = GetWorld()->SpawnActor<ADoor>(FVector(columb * 100, 0, -row * 100), FRotator(-90, 0, 0), SpawnInfo);
			Spawnedworld.Add(one);
			columb++;
			continue;
		}
		if (layer.spawn == 't')
		{
			AFloor* one = GetWorld()->SpawnActor<AFloor>(FVector(columb * 100, 1, -row * 100), FRotator(0, 0, 0), SpawnInfo);
			ATrap* two = GetWorld()->SpawnActor<ATrap>(FVector(columb * 100, 0.9, -row * 100), FRotator(0, 0, 0), SpawnInfo);
			Spawnedworld.Add(one);
			Spawnedworld.Add(two);
			columb++;
			continue;
		}
		if (layer.spawn == 'e')
		{
			AFloor* one = GetWorld()->SpawnActor<AFloor>(FVector(columb * 100, 1, -row * 100), FRotator(0, 0, 0), SpawnInfo);
			AEnemy* two = GetWorld()->SpawnActor<AEnemy>(FVector(columb * 100, -10, -row * 100), FRotator(0, 0, 0), SpawnInfo);
			Spawnedworld.Add(one);
			Spawnedworld.Add(two);
			columb++;
			continue;
		}
		if (layer.spawn == '1')
		{
			ARoof* one = GetWorld()->SpawnActor<ARoof>(FVector(columb * 100, 1, -row * 100), FRotator(0, 0, 0), SpawnInfo);
			Spawnedworld.Add(one);
			one->setSprite(1);
			columb++;
			continue;
		}
		if (layer.spawn == '2')
		{
			ARoof* one = GetWorld()->SpawnActor<ARoof>(FVector(columb * 100, 1, -row * 100), FRotator(270, 0, 0), SpawnInfo);
			Spawnedworld.Add(one);
			one->setSprite(1);
			columb++;
			continue;
		}
		if (layer.spawn == '3')
		{
			ARoof* one = GetWorld()->SpawnActor<ARoof>(FVector(columb * 100, 1, -row * 100), FRotator(90, 0, 0), SpawnInfo);
			Spawnedworld.Add(one);
			one->setSprite(1);
			columb++;
			continue;
		}
		if (layer.spawn == '4')
		{
			ARoof* one = GetWorld()->SpawnActor<ARoof>(FVector(columb * 100, 1, -row * 100), FRotator(180, 0, 0), SpawnInfo);
			Spawnedworld.Add(one);
			one->setSprite(1);
			columb++;
			continue;
		}
	}
}
// Called when the game starts or when spawned
void ASpawnRoom::BeginPlay()
{
	Super::BeginPlay();
	

	LoadRoomFromFile("room1.txt");
	SortLayers();
	SpawnLayers();
//	const TCHAR* fuck = *SavedName;
	//GEngine->AddOnScreenDebugMessage(10, 5.f, FColor::Red, FString::Printf(fuck));
}

void ASpawnRoom::SpawnRoom(int i)
{
	for(int j = 0; j < Spawnedworld.Num() - 1; j++ )
	{ 
		GetWorld()->DestroyActor(Spawnedworld[j]);//	Spawnedworld[j]->DestroyActor();
		
	}
	Spawnedworld.Empty();
	FString f = "room" + FString::FromInt(i) + ".txt";
	LoadRoomFromFile(f);
	SortLayers();
	SpawnLayers();
}
void ASpawnRoom::SortLayers()
{
	int layerID = 1;
	for (int i = 0; i < SavedName.Len() ; i++)
	{
		if (SavedName[i] == '/')
		{
			layerID++;
			continue;
		}
		MyLayers.Add(FmyLayer(layerID, SavedName[i]));
	 }
}
bool ASpawnRoom::LoadRoomFromFile(FString RoomName)
{
	FString RelativePath = FPaths::GameContentDir();
	FString LoadFilePath = RelativePath + "Rooms/" + RoomName;
	const TCHAR* fuck = *LoadFilePath;
	SavedName = "";
	MyLayers.Empty();
	FFileHelper::LoadFileToString(SavedName, *LoadFilePath);

	if (SavedName != "")
	{
		return true;
	}

	return false;
}

// Called every frame
void ASpawnRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

