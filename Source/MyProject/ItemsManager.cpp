// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemsManager.h"
#include "SpawnWeapon.h"
#include "SpawnArmor.h"
#include "SpawnOtherItems.h"

// Sets default values
AItemsManager::AItemsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AItemsManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemsManager::SpawnItems(FVector position, int id, int key)
{
	FActorSpawnParameters spawnInfo;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (key <= 10)
	{
		spawnWeapon = GetWorld()->SpawnActor<ASpawnWeapon>(this->GetActorLocation(), FRotator(0, 0, 0), spawnInfo);
		spawnWeapon->SpawnWeapon(position, id);
	}
	else if (key <= 20 && key > 10)
	{
		spawnArmor = GetWorld()->SpawnActor<ASpawnArmor>(this->GetActorLocation(), FRotator(0, 0, 0), spawnInfo);
		spawnArmor->SpawnArmor(position, id);
	}
	else if (key <= 80 && key >20)
	{
		spawnOtherItems = GetWorld()->SpawnActor<ASpawnOtherItems>(this->GetActorLocation(), FRotator(0, 0, 0), spawnInfo);
		spawnOtherItems->SpawnOtherItem(position, id);
	}
	else return;
}

