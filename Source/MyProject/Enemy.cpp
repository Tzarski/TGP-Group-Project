// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UnrealType.h"
#include "ItemsManager.h"



//--------------------------------------------------------
// REDUNDANT - FOR REFERENCE ONLY
//--------------------------------------------------------

// Sets default values
AEnemy::AEnemy(const FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	defaultsprite = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("default sprite"));
	defaultsprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Art/Gen/player_Sprite.player_Sprite'")).Object);
	defaultsprite->SetupAttachment(RootComponent);
	defaultsprite->SetCollisionProfileName(TEXT("OverlapAll"));
	//RootComponent->SetCollisionProfileName(TEXT("OverlapAll"));

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemy::Hit()
{
	if (dead)
		return;
	dead = true;
	FTimerHandle    handle;
	defaultsprite->SetSpriteColor(FLinearColor(1, 0.1, 0.1, 1));
	GetWorld()->GetTimerManager().SetTimer(handle, [this]() {	this->Destroy(); }, 1, false);

	FActorSpawnParameters spawnInfo;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	itemsManager = GetWorld()->SpawnActor<AItemsManager>(GetActorLocation(), FRotator(0, 0, 0), spawnInfo);
	itemsManager->SpawnItems(this->GetActorLocation(), randomID, randomKey);
}
 
// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (dead )
		return;

	//return;//remove this just testing the a*
	if (player == NULL)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerChar::StaticClass(), foundCharacter);
		for (AActor* protag : foundCharacter)
		{
			player = Cast<APlayerChar>(protag);
		}

		return;
	}
	ticks++;
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("looping %i, "), ticks));
	
	if (pathfinder == NULL || ticks > 30)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		pathfinder = GetWorld()->SpawnActor<Anewastar>(FVector(1, 1, 1), FRotator(1, 1, 1), SpawnInfo);;
		pathfinder->Find(player->GetActorLocation(), this->GetActorLocation());
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

	if (location.X >= this->GetActorLocation().X)
	{
		defaultsprite->AddLocalOffset(FVector(3, 0, 0), true, NULL, ETeleportType::None);
	}

	if (location.X <= this->GetActorLocation().X)
	{
		defaultsprite->AddLocalOffset(FVector(-3, 0, 0), true, NULL, ETeleportType::None);
	}

	if (location.Z >= this->GetActorLocation().Z)
	{
		defaultsprite->AddLocalOffset(FVector(0, 0, 3), true, NULL, ETeleportType::None);
	}

	if (location.Z <= this->GetActorLocation().Z)
	{
		defaultsprite->AddLocalOffset(FVector(0, 0, -3), true, NULL, ETeleportType::None);
	}

}

