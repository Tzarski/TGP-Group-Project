// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Mage.h"
#include "Fireball.h"


AEnemy_Mage::AEnemy_Mage()
{
	enemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MageSprite"));
	LoadPaperSprites();
	enemySprite->SetSprite(papersprite[0]);
	enemySprite->SetupAttachment(RootComponent);
	enemySprite->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	enemySprite->SetCollisionProfileName(TEXT("OverlapAll"));
	soundEffect = CreateDefaultSubobject<USound>(TEXT("MageSounds"));
	soundEffect->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("Mage_hurt'/Game/Audio/Mage_hurt.Mage_hurt'")).Object);

	_health = 10;
	_speed = 1.5f; //Placeholder
	_range = 0; //Placeholder
	_damage = 0; //Placeholder
}

void AEnemy_Mage::LoadPaperSprites()
{
	papersprite[0] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("MageSprite'/Game/Art/Gen/player_Sprite.player_Sprite'")).Object;
}

void AEnemy_Mage::Damaged()
{
	if (dead == false)
	{
		dead = true;
		soundEffect->PlaySound();
		FTimerHandle    handle;
		enemySprite->SetSpriteColor(FLinearColor(1, 0.1, 0.1, 1));
		GetWorld()->GetTimerManager().SetTimer(handle, [this]() {	this->Destroy(); }, 1, false);
	}
}

void AEnemy_Mage::Move()
{
	if (!block)
	{
		if (sqrtf(FVector::DistSquared(_pPlayer->GetActorLocation(), this->GetActorLocation())) < 300.0f)
		{
			FVector approaching = (_pPlayer->GetActorLocation() - this->GetActorLocation());
			FRotator Rotation = FRotationMatrix::MakeFromY(approaching).Rotator();
			const FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
			enemySprite->AddLocalOffset(-FVector(Direction.X, 0.0f, Direction.Z)* _speed);
		}
	}
	if (ticks % 200 == 0)
		Attack();
	
}
void AEnemy_Mage::Attack()
{
	AFireball* fireball = GetWorld()->SpawnActor<AFireball>(this->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f), SpawnInfo);
	fireball->mageAttacking = this;
}