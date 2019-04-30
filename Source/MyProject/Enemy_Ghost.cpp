// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Ghost.h"


AEnemy_Ghost::AEnemy_Ghost()
{
	enemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("GhostSprite"));
	LoadPaperSprites();
	enemySprite->SetSprite(papersprite[0]);	
	enemySprite->SetupAttachment(RootComponent);
	enemySprite->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	enemySprite->SetCollisionProfileName(TEXT("OverlapAll"));

	soundEffect = CreateDefaultSubobject<USound>(TEXT("Ghost_dying_sound"));
	soundEffect->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("Mage_hurt'/Game/Audio/Ghost_dead.Ghost_dead'")).Object);
	
	dead = false;

	_health = 5;
	_speed = 2; //Placeholder
	_range = 0; //Placeholder
	_damage = 0; //Placeholder

	srand(GGPUFrameTime);
	randomX = 1 - ((rand() % 200) / 100.0f);
	randomZ = randomX;
}

void AEnemy_Ghost::Damaged()
{
	if (dead == false)
	{
		dead = true;
		soundEffect->PlaySound();
		FTimerHandle    handle;
		enemySprite->SetSpriteColor(FLinearColor(1, 0.1, 0.1, 1));
		GetWorld()->GetTimerManager().SetTimer(handle, [this]() {	this->Destroy(); }, 1, false);

		FActorSpawnParameters spawnInfo;
		spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		itemsManager = GetWorld()->SpawnActor<AItemsManager>(GetActorLocation(), FRotator(0, 0, 0), spawnInfo);
		itemsManager->SpawnItems(this->GetActorLocation(), randomID, randomKey);
	}
}

void AEnemy_Ghost::Move()
{
	if (ticks % 250 == 0)
	{
		randomX = 1.0f - ((rand() % 200) / 100.0f);
		randomZ = 1.0f - ((rand() % 200) / 100.0f);
	}

	if (sqrtf(FVector::DistSquared(_pPlayer->defaultsprite->GetComponentLocation(), enemySprite->GetComponentLocation())) < 500.0f)
	{
		FVector approaching = (_pPlayer->GetActorLocation() - this->GetActorLocation());
		FRotator Rotation = FRotationMatrix::MakeFromY(approaching).Rotator();		
		const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
		enemySprite->AddLocalOffset(FVector(Direction.X, 0.0f, Direction.Z) * _speed * 2);
		randomX = Direction.X;
		randomZ = Direction.Z;
		attacking = true;
	}
	else if (block)
	{
		if (rand() % 2 == 1)
		randomX = -randomX;
		else
		randomZ = -randomZ;
		enemySprite->AddLocalOffset(FVector(randomX * _speed, 0, _speed * randomZ));
	}
	else
	{			
		enemySprite->AddLocalOffset(FVector(randomX * _speed, 0 , _speed * randomZ));
	}
}

void AEnemy_Ghost::LoadPaperSprites()
{
	papersprite[0] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("GhostSprite'/Game/Art/Gen/Ghost/Ghost_Sprite_0.Ghost_Sprite_0'")).Object;
	papersprite[1] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("GhostSprite'/Game/Art/Gen/Ghost/Ghost_Sprite_1.Ghost_Sprite_1'")).Object;
	papersprite[2] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("GhostSprite'/Game/Art/Gen/Ghost/Ghost_Sprite_2.Ghost_Sprite_2'")).Object;
	papersprite[3] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("GhostSprite'/Game/Art/Gen/Ghost/Ghost_Sprite_3.Ghost_Sprite_3'")).Object;
	papersprite[4] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("GhostSprite'/Game/Art/Gen/Ghost/Ghost_Sprite_4.Ghost_Sprite_4'")).Object;
	papersprite[5] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("GhostSprite'/Game/Art/Gen/Ghost/Ghost_Sprite_5.Ghost_Sprite_5'")).Object;
	papersprite[6] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("GhostSprite'/Game/Art/Gen/Ghost/Ghost_Sprite_6.Ghost_Sprite_6'")).Object;
	papersprite[7] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("GhostSprite'/Game/Art/Gen/Ghost/Ghost_Sprite_7.Ghost_Sprite_7'")).Object;
	papersprite[8] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("GhostSprite'/Game/Art/Gen/Ghost/Ghost_Sprite_8.Ghost_Sprite_8'")).Object;
	papersprite[9] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("GhostSprite'/Game/Art/Gen/Ghost/Ghost_Sprite_9.Ghost_Sprite_9'")).Object;
	papersprite[10] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("GhostSprite'/Game/Art/Gen/Ghost/Ghost_Sprite_10.Ghost_Sprite_10'")).Object;
	papersprite[11] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("GhostSprite'/Game/Art/Gen/Ghost/Ghost_Sprite_11.Ghost_Sprite_11'")).Object;

}

void AEnemy_Ghost::SetSprites()
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
