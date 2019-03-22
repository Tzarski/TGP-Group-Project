// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "CoreMinimal.h"
#include <fstream>
#include "GameFramework/Actor.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "SpawnWeapon.generated.h"


USTRUCT()
struct FWeaponData
{
	GENERATED_BODY()


	FWeaponData()
	{

	}

	FString WeaponName;
	int AttackDamage;
	float AttackSpeed;
	int Price;

};

class AWeapon;

UCLASS()
class MYPROJECT_API ASpawnWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnWeapon();
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool LoadFromFile(FString weaponName);
	void SpawnWeapon(FVector position, int id);

	FString SavedWeapon = "";
	FVector spawnLoc;

	TArray<AWeapon*> Weapons;

	FWeaponData weaponData;
};
