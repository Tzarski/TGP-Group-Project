// Fill out your copyright notice in the Description page of Project Settings.

#include "Fireball.h"

AFireball::AFireball()
{
	enemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("fireballSprite"));
	LoadSprites();
	enemySprite->SetSprite(papersprite[0]);
	enemySprite->SetupAttachment(RootComponent);
	enemySprite->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	enemySprite->SetCollisionProfileName(TEXT("OverlapAll"));

	soundEffect = CreateDefaultSubobject<USound>(TEXT("Fireball_sound"));
	soundEffect->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("Fireball_effect'/Game/Audio/Fireball.Fireball'")).Object);
	soundEffect->PlaySound();

	_speed = 0;
}


void AFireball::LoadSprites()
{
	papersprite[0] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("Flame'/Game/Art/Gen/Fire_Sprite.Fire_Sprite'")).Object;
	papersprite[1] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("Fire'/Game/Art/Gen/Fire_hit_Sprite.Fire_hit_Sprite'")).Object;
}

void AFireball::Move()
{
	if (_speed == 0)
	{
		FVector approaching = (_pPlayer->GetActorLocation() - this->GetActorLocation());
		FRotator Rotation = FRotationMatrix::MakeFromY(approaching).Rotator();
		Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

		enemySprite->AddLocalRotation(FRotator(Rotation.Pitch, 0.0f, 0.0f));
		_speed = 4;
	}

	if (enemySprite->GetSprite() != papersprite[1])
		this->AddActorWorldOffset(Direction * _speed);
	else
		attacking = true;
	if (block)
	{
		dead = true;
		this->Destroy();
	}
}

void AFireball::SetSprites()
{
	if (attacking)
	{
		if (timer == 0)
		timer = ticks;

		if (ticks - timer > 20)
		{
			enemySprite->SetSprite(papersprite[1]);
			enemySprite->SetRelativeRotation(FRotator(0.0f, this->GetActorRotation().Yaw, this->GetActorRotation().Roll));
		}

		if (ticks - timer > 100)
		{
			dead = true;
			this->Destroy();
		}
	}
}