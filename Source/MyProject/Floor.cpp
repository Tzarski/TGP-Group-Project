
// Fill out your copyright notice in the Description page of Project Settings.

#include "Floor.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AFloor::AFloor(const FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallComponent = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("Floor"));
	//BallComponent->AttatchTo(GetDefaultAttachComponent());
	BallComponent->SetupAttachment(RootComponent);


}

void AFloor::SetSprite(UPaperSpriteComponent* floor)
{
	BallComponent->SetSprite(floor->GetSprite());
}
// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

