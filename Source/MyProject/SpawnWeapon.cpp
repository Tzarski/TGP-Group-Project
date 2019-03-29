// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnWeapon.h"
#include "Weapon.h"

ASpawnWeapon::ASpawnWeapon(const FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TempComp1 = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("TempComp1"));
}

// Called when the game starts or when spawned
void ASpawnWeapon::BeginPlay()
{
	Super::BeginPlay();
	LoadFromFile("1.txt");
	
}

// Called every frame
void ASpawnWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASpawnWeapon::LoadFromFile(FString weapon)
{
	FString RelativePath = FPaths::GameContentDir();
	FString LoadFilePath = RelativePath + "Items/Weapons " + weapon;

	FFileHelper::LoadFileToString(SavedWeapon, *LoadFilePath);

	if (SavedWeapon != "")
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("Text Loaded"));
		//weaponData.WeaponName = SavedWeapon.Left(10);
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("LSavedWeapon"));
		FString tempName;
		FString tempAttack;
		UE_LOG(LogTemp, Display, TEXT("Weapon name %s"), *SavedWeapon);
		//SavedWeapon.Split(TEXT(","), &tempName, &tempAttack, ESearchCase::CaseSensitive, ESearchDir::FromStart);
		//weaponData.WeaponName = tempName;
		//.Split(SavedWeapon, 0, 10, ESearchCase::CaseSensitive, ESearchDir::FromStart);
		return true;
	}


	return false;
}

void ASpawnWeapon::SpawnWeapon(FVector position, int id)
{
	FActorSpawnParameters spawnInfo;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	weapons = GetWorld()->SpawnActor<AWeapon>(GetActorLocation(), FRotator(0, 0, 0), spawnInfo);
	weapons->SetWeaponSprite(id);
}


