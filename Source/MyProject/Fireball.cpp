// Fill out your copyright notice in the Description page of Project Settings.

#include "Fireball.h"
#include "Enemy_Mage.h"

AFireball::AFireball()
{
	enemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("FireballSprite"));
	LoadSprites();
	enemySprite->SetSprite(papersprite[0]);
	enemySprite->SetupAttachment(RootComponent);
	enemySprite->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	enemySprite->SetCollisionProfileName(TEXT("OverlapAll"));

	soundEffect = CreateDefaultSubobject<USound>(TEXT("Fireball_sound"));
	soundEffect->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("Fireball_effect'/Game/Audio/Fireball.Fireball'")).Object);
	soundEffect->PlaySound();

	sound2 = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("Fireball_hit_effect'/Game/Audio/Fire.Fire'")).Object;

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

		if (approaching.X >= 0 && approaching.Z <= 0)
		enemySprite->AddLocalRotation(FRotator(Rotation.Pitch, 0.0f, 0.0f));
		else if (approaching.X >= 0 && approaching.Z > 0)
			enemySprite->AddLocalRotation(FRotator(-180.0f - Rotation.Pitch, 0.0f, 0.0f));
		else if (approaching.X < 0 && approaching.Z <= 0)
			enemySprite->AddLocalRotation(FRotator(-Rotation.Pitch, 0.0f, 0.0f));
		else if (approaching.X < 0 && approaching.Z > 0)
			enemySprite->AddLocalRotation(FRotator(Rotation.Pitch + 180.0f, 0.0f, 0.0f));
		_speed = 4;
	}

	if (enemySprite->GetSprite() != papersprite[1])
		this->AddActorWorldOffset(FVector(Direction.X, 0.0f, Direction.Z) * _speed);
	else					
		attacking = true;
	
	if (block || mageAttacking->IsActorBeingDestroyed())
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

		if (ticks - timer > 10 && enemySprite->GetSprite() != papersprite[1])
		{
			soundEffect->SetSound(sound2);
			soundEffect->PlaySound();
			enemySprite->SetSprite(papersprite[1]);
			if (Direction.Z < 0)
			enemySprite->SetRelativeRotation(FRotator(0.0f, enemySprite->GetComponentRotation().Yaw, enemySprite->GetComponentRotation().Roll));
			else
				enemySprite->SetRelativeRotation(FRotator(180.0f, enemySprite->GetComponentRotation().Yaw, enemySprite->GetComponentRotation().Roll));
		}

		if (ticks - timer > 100)
		{
			soundEffect->StopSound();
			dead = true;
			this->Destroy();
		}
	}
}