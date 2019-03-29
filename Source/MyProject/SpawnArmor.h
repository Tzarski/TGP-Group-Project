// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "SpawnArmor.generated.h"

class AArmor;

USTRUCT()
struct FArmorData
{
	GENERATED_BODY()


	FArmorData()
	{

	}

	FString ArmorName;
	int Defence;
	int Price;

};

UCLASS()
class MYPROJECT_API ASpawnArmor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnArmor(const FObjectInitializer& PCIP);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool LoadFromFile(FString armor);
	void SpawnArmor(FVector position, int id);
	
	AArmor* armor;
	FString SavedArmor = "";
	FArmorData armorData;
	class UPaperSpriteComponent* TempComp1;
};
