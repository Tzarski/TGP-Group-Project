// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Splitter.h"

// Sets default values
AEnemy_Splitter::AEnemy_Splitter() 
{
	enemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SplitterSprite"));
	LoadPaperSprites();
	enemySprite->SetSprite(papersprite[0]);
	enemySprite->SetupAttachment(RootComponent);
	enemySprite->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	enemySprite->SetCollisionProfileName(TEXT("OverlapAll"));

	soundEffect = CreateDefaultSubobject<USound>(TEXT("Splitter_dying_sound"));
	//soundEffect->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("Mage_hurt'/Game/Audio/Ghost_dead.Ghost_dead'")).Object); - Find sound

	_health = 15;
	_speed = 0; //Placeholder
	_range = 0; //Placeholder
	_damage = 0; //Placeholder
}

void AEnemy_Splitter::LoadPaperSprites()
{
	papersprite[0] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("SplitterSprite'/Game/Art/Gen/Splitter/Splitter_Sprite_0.Splitter_Sprite_0'")).Object;
	papersprite[1] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("SplitterSprite'/Game/Art/Gen/Splitter/Splitter_Sprite_1.Splitter_Sprite_1'")).Object;
	papersprite[2] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("SplitterSprite'/Game/Art/Gen/Splitter/Splitter_Sprite_2.Splitter_Sprite_2'")).Object;
	papersprite[3] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("SplitterSprite'/Game/Art/Gen/Splitter/Splitter_Sprite_3.Splitter_Sprite_3'")).Object;
	papersprite[4] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("SplitterSprite'/Game/Art/Gen/Splitter/Splitter_Sprite_4.Splitter_Sprite_4'")).Object;
	papersprite[5] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("SplitterSprite'/Game/Art/Gen/Splitter/Splitter_Sprite_5.Splitter_Sprite_5'")).Object;
	papersprite[6] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("SplitterSprite'/Game/Art/Gen/Splitter/Splitter_Sprite_6.Splitter_Sprite_6'")).Object;
	papersprite[7] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("SplitterSprite'/Game/Art/Gen/Splitter/Splitter_Sprite_7.Splitter_Sprite_7'")).Object;
	papersprite[8] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("SplitterSprite'/Game/Art/Gen/Splitter/Splitter_Sprite_8.Splitter_Sprite_8'")).Object;
	papersprite[9] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("SplitterSprite'/Game/Art/Gen/Splitter/Splitter_Sprite_9.Splitter_Sprite_9'")).Object;
	papersprite[10] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("SplitterSprite'/Game/Art/Gen/Splitter/Splitter_Sprite_10.Splitter_Sprite_10'")).Object;
	papersprite[11] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("SplitterSprite'/Game/Art/Gen/Splitter/Splitter_Sprite_11.Splitter_Sprite_11'")).Object;
}

void AEnemy_Splitter::Damaged()
{
	dead = true;
	FTimerHandle    handle;
	enemySprite->SetSpriteColor(FLinearColor(1, 0.1, 0.1, 1));
	GetWorld()->GetTimerManager().SetTimer(handle, [this]() {	this->Destroy(); }, 1, false);
}

void AEnemy_Splitter::Move()
{

}

void AEnemy_Splitter::Attack()
{

}

