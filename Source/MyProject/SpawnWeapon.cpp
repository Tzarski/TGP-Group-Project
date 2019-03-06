// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnWeapon.h"
#include "Weapon.h"


// Sets default values
ASpawnWeapon::ASpawnWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASpawnWeapon::LoadFromFile(FString weapon)
{
	FString RelativePath = FPaths::GameContentDir();
	FString LoadFilePath = RelativePath + "Weapons/" + weapon;

	FFileHelper::LoadFileToString(SavedWeapon, *LoadFilePath);

	if (!SavedWeapon.IsEmpty())
	{
		for (int i = 0; i < sizeof(SavedWeapon); i++)
		{
			
		}
	}


	return false;
}

void ASpawnWeapon::SpawnWeapon()
{

}

