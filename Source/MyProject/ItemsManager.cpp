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
	FActorSpawnParameters spawnInfo;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	spawnWeapon = GetWorld()->SpawnActor<ASpawnWeapon>(GetActorLocation(), FRotator(0, 0, 0), spawnInfo);
	spawnArmor = GetWorld()->SpawnActor<ASpawnArmor>(GetActorLocation(), FRotator(0, 0, 0), spawnInfo);
	spawnOtherItems = GetWorld()->SpawnActor<ASpawnOtherItems>(GetActorLocation(), FRotator(0, 0, 0), spawnInfo);


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
	if (key == 4, 5, 15)
	{
		spawnWeapon->SpawnWeapon(position, id);
	}

	if (key == 12, 3, 5)
	{
		spawnArmor->SpawnArmor(position, id);
	}

	if (key == 1,2,6,7,8,9,10,11,13,14)
	{
		spawnOtherItems->SpawnOtherItem(position, id);
	}


	//switch (key)
	//{	

	//	default:
	//		break;
	//}
}

