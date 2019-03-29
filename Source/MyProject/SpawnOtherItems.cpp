// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnOtherItems.h"
#include "OtherItems.h"

// Sets default values
ASpawnOtherItems::ASpawnOtherItems(const FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TempComp1 = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("TempComp1"));
}

// Called when the game starts or when spawned
void ASpawnOtherItems::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnOtherItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASpawnOtherItems::LoadFromFile(FString item)
{
	FString RelativePath = FPaths::GameContentDir();
	FString LoadFilePath = RelativePath + "Items/Weapons " + item;

	FFileHelper::LoadFileToString(SavedItem, *LoadFilePath);

	if (SavedItem != "")
	{
		return true;
		//to be added the text file attributes
	}

	return false;
}

void ASpawnOtherItems::SpawnOtherItem(FVector position, int id)
{
	FActorSpawnParameters spawnInfo;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	otherItems = GetWorld()->SpawnActor<AOtherItems>(GetActorLocation(), FRotator(0, 0, 0), spawnInfo);
	otherItems->SetItemID(id);
}

