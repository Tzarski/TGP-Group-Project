// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnOtherItems.h"
#include "Kismet/GameplayStatics.h"
#include "OtherItems.h"

// Sets default values
ASpawnOtherItems::ASpawnOtherItems()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnOtherItems::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> foundCharacter;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGlobals::StaticClass(), foundCharacter);
	for (AActor* protag : foundCharacter)
	{
		GlobVars = Cast<AGlobals>(protag);
	}
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
	otherItems = GetWorld()->SpawnActor<AOtherItems>(position, FRotator(0, 0, 0), spawnInfo);
	otherItems->SetItemID(id);
	GlobVars->ExtraToClear.Add(otherItems);

}

