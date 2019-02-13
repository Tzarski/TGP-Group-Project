// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"


// Sets default values
ADoor::ADoor(const FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BallComponent = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("ball"));
	//BallComponent->AttatchTo(GetDefaultAttachComponent());
	BallComponent->SetupAttachment(RootComponent);
	BallComponent->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Art/Gen/dooor_Sprite.dooor_Sprite'")).Object);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

