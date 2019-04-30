// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "StringConv.h"
#include "UnrealString.h"
#include "NameTypes.h"
#include "cstring"
#include "Weapon.h"

ASpawnWeapon::ASpawnWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnWeapon::BeginPlay()
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
void ASpawnWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ASpawnWeapon::LoadFromFile(FString weapon)
{
	FString RelativePath = FPaths::GameContentDir();
	FString LoadFilePath = RelativePath + "Items/Weapons/ " + weapon;

	FFileHelper::LoadFileToString(SavedWeapon, *LoadFilePath);

	if (SavedWeapon != "")
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("Text File Loaded"));

		for (int i = 0; i < SavedWeapon.Len(); i++)
		{
			if (SavedWeapon[i] == '/')
			{
				weaponData.WeaponName = "" + SavedWeapon[0];
				weaponData.AttackDamage = FCString::Atoi(&SavedWeapon[1]);
				weaponData.AttackSpeed = FCString::Atof(&SavedWeapon[2]);
				weaponData.Price = FCString::Atoi(&SavedWeapon[3]);
			}
		}

		return true;
	}

	return false;
}

void ASpawnWeapon::SpawnWeapon(FVector position, int id)
{
	FActorSpawnParameters spawnInfo;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	weapons = GetWorld()->SpawnActor<AWeapon>(position, FRotator(0, 0, 0), spawnInfo);
	weapons->SetWeaponSprite(id);
	LoadFromFile( id + ".txt");

	GlobVars->ExtraToClear.Add(weapons);
}


