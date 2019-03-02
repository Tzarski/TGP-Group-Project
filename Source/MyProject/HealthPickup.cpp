// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthPickup.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSprite.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "PlayerChar.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values
AHealthPickup::AHealthPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("health+"));
	HealthSprite->SetupAttachment(RootComponent);
	HealthSprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Art/Gen/Health_test_Sprite.Health_test_Sprite'")).Object);
}

// Called when the game starts or when spawned
void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGlobals::StaticClass(), locateValues);
	for (AActor* playerValues : locateValues)
	{
		characterValues = Cast<AGlobals>(playerValues);
	}	
}

// Called every frame
void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (character == NULL)
	{
		locateValues.Empty();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerChar::StaticClass(), locateValues);
		for (AActor* player : locateValues)
		{
			character = Cast<APlayerChar>(player);
		}
	}

	if (FMath::Sqrt((character->GetActorLocation() - GetActorLocation()).SizeSquared()) < 75)
	{
		if (characterValues->health < 2)
		{
			characterValues->Heal(1);	

			this->Destroy();
		}
	}
}

