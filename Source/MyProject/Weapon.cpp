// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AWeapon::AWeapon(const FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WeaponComponent = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("weapon"));
	WeaponComponent->SetupAttachment(RootComponent);
	TempComp1 = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("TempComp1"));
	TempComp1->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Items/Weapons/sword1_Sprite.sword1_Sprite'")).Object);
	TempComp2 = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("TempComp2"));
	TempComp2->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Items/Weapons/sword2_Sprite.sword2_Sprite'")).Object);
	TempComp1->SetVisibility(false, false);
	TempComp2->SetVisibility(false, false);

	
	
	/*if (weaponID == 1)
	{
		WeaponComponent->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Items/Weapons/sword1_Sprite.sword1_Sprite'")).Object);
	}
	if (weaponID == 2)
	{
		WeaponComponent->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Items/Weapons/sword2_Sprite.sword2_Sprite'")).Object);
	}*/
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}
void AWeapon::SetWeaponSprite(int i)
{
	switch (i)
	{
	case 1:
		WeaponComponent->SetSprite(TempComp1->GetSprite());
		break;
	case 2:
		WeaponComponent->SetSprite(TempComp2->GetSprite());
		break;

	}
	
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

