// Fill out your copyright notice in the Description page of Project Settings.

#include "Roof.h"


// Sets default values
ARoof::ARoof(const FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	defaultsprite = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("wall sprite"));
	defaultsprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Art/Gen/wall_Sprite.wall_Sprite'")).Object);
	sprite1 = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("corner wall sprite"));
	sprite1->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Art/Gen/corner_Sprite.corner_Sprite'")).Object);
	sprite2 = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("Broken"));
	sprite2->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Art/Gen/broken_Sprite.broken_Sprite'")).Object);
	defaultsprite->SetupAttachment(RootComponent);
	//setSprite(0);
	//BallComponent->AttatchTo(GetDefaultAttachComponent());
	

}

// Called when the game starts or when spawned
void ARoof::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARoof::setSprite(int i)
{	
	switch (i)
	{
		case 0:
			sprite2->SetSprite(NULL);
			sprite1->SetSprite(NULL);
		break;
		case 1:
			//defaultsprite->SetupAttachment(RootComponent);
			defaultsprite->SetSprite(sprite1->GetSprite());
			sprite1->SetSprite(NULL);
			sprite2->SetSprite(NULL);
		break;
		case 2:
			//defaultsprite->SetupAttachment(RootComponent);
			defaultsprite->SetSprite(sprite2->GetSprite());
			sprite1->SetSprite(NULL);
			sprite2->SetSprite(NULL);
			break;
		default:
			break;
	}
	return;

}

// Called every frame
void ARoof::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

