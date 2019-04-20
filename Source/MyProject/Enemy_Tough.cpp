// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Tough.h"

AEnemy_Tough::AEnemy_Tough()
{
	enemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ToughSprite"));
	LoadPaperSprites();
	enemySprite->SetSprite(papersprite[0]);
	enemySprite->SetupAttachment(RootComponent);
	enemySprite->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	enemySprite->SetCollisionProfileName(TEXT("OverlapAll"));

	soundEffect = CreateDefaultSubobject<USound>(TEXT("Tough_dying_sound"));
	//soundEffect->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("Mage_hurt'/Game/Audio/Ghost_dead.Ghost_dead'")).Object); - Find sound

	_health = 15;
	_speed = 1; 
	_range = 0; //Placeholder
	_damage = 0; //Placeholder

	srand(GGPUFrameTime);
	randomX = 1 - ((rand() % 200) / 100.0f);
	randomZ = randomX;
}

void AEnemy_Tough::LoadPaperSprites()
{
	papersprite[0] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ToughSprite'/Game/Art/Gen/Ogre/Ogre_Sprite_0.Ogre_Sprite_0'")).Object;
	papersprite[1] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ToughSprite'/Game/Art/Gen/Ogre/Ogre_Sprite_1.Ogre_Sprite_1'")).Object;
	papersprite[2] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ToughSprite'/Game/Art/Gen/Ogre/Ogre_Sprite_2.Ogre_Sprite_2'")).Object;
	papersprite[3] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ToughSprite'/Game/Art/Gen/Ogre/Ogre_Sprite_3.Ogre_Sprite_3'")).Object;
	papersprite[4] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ToughSprite'/Game/Art/Gen/Ogre/Ogre_Sprite_4.Ogre_Sprite_4'")).Object;
	papersprite[5] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ToughSprite'/Game/Art/Gen/Ogre/Ogre_Sprite_5.Ogre_Sprite_5'")).Object;
	papersprite[6] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ToughSprite'/Game/Art/Gen/Ogre/Ogre_Sprite_6.Ogre_Sprite_6'")).Object;
	papersprite[7] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ToughSprite'/Game/Art/Gen/Ogre/Ogre_Sprite_7.Ogre_Sprite_7'")).Object;
	papersprite[8] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ToughSprite'/Game/Art/Gen/Ogre/Ogre_Sprite_8.Ogre_Sprite_8'")).Object;
	papersprite[9] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ToughSprite'/Game/Art/Gen/Ogre/Ogre_Sprite_9.Ogre_Sprite_9'")).Object;
	papersprite[10] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ToughSprite'/Game/Art/Gen/Ogre/Ogre_Sprite_10.Ogre_Sprite_10'")).Object;
	papersprite[11] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ToughSprite'/Game/Art/Gen/Ogre/Ogre_Sprite_11.Ogre_Sprite_11'")).Object;
}

void AEnemy_Tough::SetSprites()
{
	if (FMath::Square(randomX) <= FMath::Square(randomZ) && randomZ < 0)
	{
		spriteSelected = 0;
	}
	else if (FMath::Square(randomX) >= FMath::Square(randomZ) && randomX < 0)
	{
		spriteSelected = 3;
	}
	else if (FMath::Square(randomX) <= FMath::Square(randomZ) && randomZ >= 0)
	{
		spriteSelected = 9;
	}
	else if (FMath::Square(randomX) >= FMath::Square(randomZ) && randomX >= 0)
	{
		spriteSelected = 6;
	}


	if (ticks % 10 == 0)
	{
		if (attacking)
		{
			spriteSelected = spriteSelected + 2;
		}
		else
		{
			spriteSelected = spriteSelected + changeSprite;
			if (changeSprite == 1)
				changeSprite--;
			else
				changeSprite = 1;
		}
		enemySprite->SetSprite(papersprite[spriteSelected]);
		attacking = false;
	}
}

void AEnemy_Tough::Damaged()
{
	dead = true;
	//soundEffect->PlaySound();
	FTimerHandle    handle;
	enemySprite->SetSpriteColor(FLinearColor(1, 0.1, 0.1, 1));
	GetWorld()->GetTimerManager().SetTimer(handle, [this]() {	this->Destroy(); }, 1, false);
}

void AEnemy_Tough::Move()
{

}

void AEnemy_Tough::Attack()
{

}


