// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Ghost.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UnrealType.h"

AEnemy_Ghost::AEnemy_Ghost()
{
	enemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("enemySprite"));
	enemySprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("GhostSprite'/Game/Art/Gen/Ghost/Ghost_Sprite_0.Ghost_Sprite_0'")).Object);
	enemySprite->SetupAttachment(RootComponent);
	enemySprite->SetCollisionProfileName(TEXT("OverlapAll"));

	dead = false;

	_health = 5;
	_speed = 0; //Placeholder
	_range = 0; //Placeholder
	_damage = 0; //Placeholder
}

void AEnemy_Ghost::Damaged()
{
	dead = true;
	FTimerHandle    handle;
	enemySprite->SetSpriteColor(FLinearColor(1, 0.1, 0.1, 1));
	GetWorld()->GetTimerManager().SetTimer(handle, [this]() {	this->Destroy(); }, 1, false);
}
