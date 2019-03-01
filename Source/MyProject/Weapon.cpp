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
	WeaponComponent->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Art/Weapons/'")).Object);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

