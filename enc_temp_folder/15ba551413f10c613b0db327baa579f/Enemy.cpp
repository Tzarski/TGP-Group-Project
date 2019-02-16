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

void AEnemy::Hit()
{
	dead = true;
	FTimerHandle    handle;
	defaultsprite->SetSpriteColor(FLinearColor(1, 0.1, 0.1, 1));
	GetWorld()->GetTimerManager().SetTimer(handle, [this]() {	this->Destroy(); }, 1, false);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (dead)
		return;
	if (player == NULL)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerChar::StaticClass(), foundCharacter);
		for (AActor* protag : foundCharacter)
		{
			player = Cast<APlayerChar>(protag);
		}
		return;
	}
	if (player->dead)
		return;
	//DrawDebugSphere(GetWorld(), this->GetActorLocation(), 70, 70, FColor::Red, true, 2, 0, 10);

	TArray<FHitResult> OutHits;
	FVector SweepStart = this->GetActorLocation();
	FVector SweepEnd = this->GetActorLocation();
	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(70.0f);

	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, SweepStart, SweepEnd, FQuat::Identity, ECC_WorldStatic, MyColSphere);
	bool cantmove = false;

	if (isHit)
	{
		for (auto& Hit : OutHits)
		{
			if (GEngine)
			{
				if (Hit.Actor->GetName().Contains("player", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					Cast<APlayerChar>(Hit.Actor)->TakeDamage();
					
					return;
				}
			}
		}
	}
	FVector location = player->GetActorLocation();
	if (location.X > this->GetActorLocation().X + 4)
	{
		defaultsprite->AddLocalOffset(FVector(3, 0, 0), true, NULL, ETeleportType::None);
	}

	if (location.X < this->GetActorLocation().X - 4)
	{
		defaultsprite->AddLocalOffset(FVector(-3, 0, 0), true, NULL, ETeleportType::None);
	}

	if (location.Z > this->GetActorLocation().Z + 4)
	{
		defaultsprite->AddLocalOffset(FVector(0, 0, 3), true, NULL, ETeleportType::None);
	}

	if (location.Z < this->GetActorLocation().Z - 4)
	{
		defaultsprite->AddLocalOffset(FVector(0, 0, -3), true, NULL, ETeleportType::None);
	}



}

