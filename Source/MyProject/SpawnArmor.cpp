// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnArmor.h"
#include "Armor.h"

// Sets default values
ASpawnArmor::ASpawnArmor(const FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TempComp1 = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("TempComp1"));
}

// Called when the game starts or when spawned
void ASpawnArmor::BeginPlay()
{
	Super::BeginPlay();
	
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
	armor = GetWorld()->SpawnActor<AArmor>(GetActorLocation(), FRotator(0, 0, 0), spawnInfo);
	armor->SetArmorID(id);
}

