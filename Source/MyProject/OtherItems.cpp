// Fill out your copyright notice in the Description page of Project Settings.

#include "OtherItems.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AOtherItems::AOtherItems(const FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemComponent = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("otheritems"));
	ItemComponent->SetupAttachment(RootComponent);

	TempComp1 = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("TempComp1"));
	TempComp1->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Items/OtherItems/CannedFood_Sprite.CannedFood_Sprite'")).Object);

	TempComp2 = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("TempComp2"));
	TempComp2->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Items/OtherItems/FreshFood_Sprite.FreshFood_Sprite'")).Object);

	TempComp1->SetVisibility(false, false);
	TempComp2->SetVisibility(false, false);
}

void AOtherItems::SetItemID(int id)
{
	switch (id)
	{
	case 1:
		ItemComponent->SetSprite(TempComp1->GetSprite());
		break;
	case 2:
		ItemComponent->SetSprite(TempComp2->GetSprite());
		break;

	}
}

// Called when the game starts or when spawned
void AOtherItems::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOtherItems::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

