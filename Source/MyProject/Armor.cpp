// Fill out your copyright notice in the Description page of Project Settings.

#include "Armor.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AArmor::AArmor(const FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ArmorComponent = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("armor"));
	ArmorComponent->SetupAttachment(RootComponent);

	TempComp1 = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("TempComp1"));
	TempComp1->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Items/Armor/armor1_Sprite.armor1_Sprite'")).Object);

	TempComp2 = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("TempComp2"));
	TempComp2->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Items/Armor/armor2_Sprite.armor2_Sprite'")).Object);

	TempComp1->SetVisibility(false, false);
	TempComp2->SetVisibility(false, false);
}

void AArmor::SetArmorID(int id)
{
	switch (id)
	{
	case 1:
		ArmorComponent->SetSprite(TempComp1->GetSprite());
		break;
	case 2:
		ArmorComponent->SetSprite(TempComp2->GetSprite());
		break;
	default:
		break;

	}
}

// Called when the game starts or when spawned
void AArmor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArmor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

