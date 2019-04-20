// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_SplitterChild.h"

// Sets default values
AEnemy_SplitterChild::AEnemy_SplitterChild()
{
	enemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ChildSprite"));
	LoadPaperSprites();
	enemySprite->SetSprite(papersprite[0]);
	enemySprite->SetupAttachment(RootComponent);
	enemySprite->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	enemySprite->SetCollisionProfileName(TEXT("OverlapAll"));

	soundEffect = CreateDefaultSubobject<USound>(TEXT("Child_dying_sound"));
	//soundEffect->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("Mage_hurt'/Game/Audio/Ghost_dead.Ghost_dead'")).Object); - Find sound

	_health = 15;
	_speed = 0; //Placeholder
	_range = 0; //Placeholder
	_damage = 0; //Placeholder

	srand(GGPUFrameTime);
	randomX = 1 - ((rand() % 200) / 100.0f);
	randomZ = randomX;
}

void AEnemy_SplitterChild::LoadPaperSprites()
{
	papersprite[0] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ChildSprite'/Game/Art/Gen/Splitter/Splitter_child_Sprite_0.Splitter_child_Sprite_0'")).Object;
	papersprite[1] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ChildSprite'/Game/Art/Gen/Splitter/Splitter_child_Sprite_1.Splitter_child_Sprite_1'")).Object;
	papersprite[2] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ChildSprite'/Game/Art/Gen/Splitter/Splitter_child_Sprite_2.Splitter_child_Sprite_2'")).Object;
	papersprite[3] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ChildSprite'/Game/Art/Gen/Splitter/Splitter_child_Sprite_3.Splitter_child_Sprite_3'")).Object;
	papersprite[4] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ChildSprite'/Game/Art/Gen/Splitter/Splitter_child_Sprite_4.Splitter_child_Sprite_4'")).Object;
	papersprite[5] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ChildSprite'/Game/Art/Gen/Splitter/Splitter_child_Sprite_5.Splitter_child_Sprite_5'")).Object;
	papersprite[6] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ChildSprite'/Game/Art/Gen/Splitter/Splitter_child_Sprite_6.Splitter_child_Sprite_6'")).Object;
	papersprite[7] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ChildSprite'/Game/Art/Gen/Splitter/Splitter_child_Sprite_7.Splitter_child_Sprite_7'")).Object;
	papersprite[8] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ChildSprite'/Game/Art/Gen/Splitter/Splitter_child_Sprite_8.Splitter_child_Sprite_8'")).Object;
	papersprite[9] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ChildSprite'/Game/Art/Gen/Splitter/Splitter_child_Sprite_9.Splitter_child_Sprite_9'")).Object;
	papersprite[10] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ChildSprite'/Game/Art/Gen/Splitter/Splitter_child_Sprite_10.Splitter_child_Sprite_10'")).Object;
	papersprite[11] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("ChildSprite'/Game/Art/Gen/Splitter/Splitter_child_Sprite_11.Splitter_child_Sprite_11'")).Object;
}

void AEnemy_SplitterChild::SetSprites()
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

void AEnemy_SplitterChild::Damaged()
{
	dead = true;
	//soundEffect->PlaySound();
	FTimerHandle    handle;
	enemySprite->SetSpriteColor(FLinearColor(1, 0.1, 0.1, 1));
	GetWorld()->GetTimerManager().SetTimer(handle, [this]() {	this->Destroy(); }, 1, false);
}

void AEnemy_SplitterChild::Move()
{

}

void AEnemy_SplitterChild::Attack()
{

}



