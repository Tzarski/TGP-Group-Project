// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UnrealType.h"

// Sets default values
AEnemy::AEnemy(const FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	defaultsprite = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("default sprite"));
	defaultsprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Art/Gen/player_Sprite.player_Sprite'")).Object);
	defaultsprite->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerChar::StaticClass(), foundCharacter);
	for (AActor* protag : foundCharacter)
	{
		player = Cast<APlayerChar>(protag);
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FVector location = player->GetActorLocation();
	
	if (location.X > this->GetActorLocation().X + 5)
	{
		defaultsprite->AddLocalOffset(FVector(5, 0, 0), true, NULL, ETeleportType::None);
	//	RootComponent->AddLocalOffset()
		//this->SetActorLocation(FVector(this->GetActorLocation().X + 5, this->GetActorLocation().Y, this->GetActorLocation().Z ));
	}

	if (location.X < this->GetActorLocation().X - 5)
	{
		defaultsprite->AddLocalOffset(FVector(-5, 0, 0), true, NULL, ETeleportType::None);
		//this->SetActorLocation(FVector(this->GetActorLocation().X - 5, this->GetActorLocation().Y, this->GetActorLocation().Z));
	}

	if (location.Z > this->GetActorLocation().Z + 5)
	{
		defaultsprite->AddLocalOffset(FVector(0, 0, 5), true, NULL, ETeleportType::None);
		//this->SetActorLocation(FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z + 5));
	}

	if (location.Z < this->GetActorLocation().Z - 5)
	{
		defaultsprite->AddLocalOffset(FVector(0, 0, -5), true, NULL, ETeleportType::None);
		//this->SetActorLocation(FVector(this->GetActorLocation().X, this->GetActorLocation().Y, this->GetActorLocation().Z - 5));
	}


}

