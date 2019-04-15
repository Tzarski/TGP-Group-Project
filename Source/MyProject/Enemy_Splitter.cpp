// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Splitter.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UnrealType.h"

// Sets default values
AEnemy_Splitter::AEnemy_Splitter() 
{
	enemySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("default sprite"));
	enemySprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Art/Gen/Splitter/Splittter_Sprite_0.Splittter_Sprite_0'")).Object);
	enemySprite->SetupAttachment(RootComponent);
	enemySprite->SetCollisionProfileName(TEXT("OverlapAll"));

	_health = 15;
	_speed = 0; //Placeholder
	_range = 0; //Placeholder
	_damage = 0; //Placeholder
}

void AEnemy_Splitter::Damaged()
{
	dead = true;
	FTimerHandle    handle;
	enemySprite->SetSpriteColor(FLinearColor(1, 0.1, 0.1, 1));
	GetWorld()->GetTimerManager().SetTimer(handle, [this]() {	this->Destroy(); }, 1, false);
}



//void AEnemy_Splitter::Attack()
//{
//	// Transfer attack stuff.
//}

