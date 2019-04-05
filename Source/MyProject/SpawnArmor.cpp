// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnArmor.h"
#include "Kismet/GameplayStatics.h"
#include "Armor.h"

// Sets default values
ASpawnArmor::ASpawnArmor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnArmor::BeginPlay()
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
void ASpawnArmor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASpawnArmor::LoadFromFile(FString armor)
{
	FString RelativePath = FPaths::GameContentDir();
	FString LoadFilePath = RelativePath + "Items/Weapons " + armor;

	FFileHelper::LoadFileToString(SavedArmor, *LoadFilePath);

	if (SavedArmor != "")
	{
		return true;
		//to be added the text file attributes
	}

	return false;
}

void ASpawnArmor::SpawnArmor(FVector position, int id)
{
	FActorSpawnParameters spawnInfo;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	armor = GetWorld()->SpawnActor<AArmor>(position, FRotator(0, 0, 0), spawnInfo);
	armor->SetArmorID(id);
	GlobVars->ExtraToClear.Add(armor);
}

