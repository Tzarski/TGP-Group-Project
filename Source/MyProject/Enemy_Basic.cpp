// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Basic.h"

// Sets default values
AEnemy_Basic::AEnemy_Basic() 
{
	enemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Basic_sprite"));
	enemySprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Art/Gen/Goblin/goblin_Sprite_0.goblin_Sprite_0'")).Object);
	enemySprite->SetupAttachment(RootComponent);
	enemySprite->SetCollisionProfileName(TEXT("OverlapAll"));

	_health = 10;
	_speed = 0; //Placeholder
	_range = 0; //Placeholder
	_damage = 0; //Placeholder
}

void AEnemy_Basic::Damaged()
{
	dead = true;
	FTimerHandle    handle;
	enemySprite->SetSpriteColor(FLinearColor(1, 0.1, 0.1, 1));
	GetWorld()->GetTimerManager().SetTimer(handle, [this]() {	this->Destroy(); }, 1, false);
}

//void AEnemy_Basic::Attack()
//{
//	// Transfer attack stuff.
//}



