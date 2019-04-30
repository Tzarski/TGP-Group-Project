// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include <EngineGlobals.h>
#include "Globals.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "SpawnOtherItems.generated.h"

class AOtherItems;

USTRUCT()
struct FItemData
{
	GENERATED_BODY()


	FItemData()
	{

	}

	FString name;
	int Price;

};

UCLASS()
class MYPROJECT_API ASpawnOtherItems : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnOtherItems();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool LoadFromFile(FString item);
	void SpawnOtherItem(FVector position, int id);
	AGlobals* GlobVars;
	AOtherItems* otherItems;
	FString SavedItem = "";
	FItemData itemData;
	
};
