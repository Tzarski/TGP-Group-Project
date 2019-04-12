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
	FString LoadFilePath = RelativePath + "Items/Armor/ " + armor;

	FFileHelper::LoadFileToString(SavedArmor, *LoadFilePath);

	if (SavedArmor != "")
	{
		for (int i = 0; i < SavedArmor.Len(); i++)
		{
			if (SavedArmor[i] == '/')
			{
				armorData.ArmorName = "" + SavedArmor[0];
				armorData.Defence = FCString::Atoi(&SavedArmor[1]);
				armorData.Price = FCString::Atoi(&SavedArmor[2]);
			}
		}

		return true;
	}

	return false;
}

void ASpawnArmor::SpawnArmor(FVector position, int id)
{
	FActorSpawnParameters spawnInfo;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	armor = GetWorld()->SpawnActor<AArmor>(position, FRotator(0, 0, 0), spawnInfo);
	armor->SetArmorID(id);
	LoadFromFile(id + ".txt");

	GlobVars->ExtraToClear.Add(armor);
}

