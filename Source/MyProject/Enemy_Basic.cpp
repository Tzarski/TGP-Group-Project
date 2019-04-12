// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Basic.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UnrealType.h"

// Sets default values
AEnemy_Basic::AEnemy_Basic(const FObjectInitializer& PCIP) : Super(PCIP)
{
	enemySprite = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("default sprite"));
	enemySprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Art/Gen/player_Sprite.player_Sprite'")).Object);
	enemySprite->SetupAttachment(RootComponent);
	enemySprite->SetCollisionProfileName(TEXT("OverlapAll"));

	_health = 10;
	_speed = 0; //Placeholder
	_range = 0; //Placeholder
	_damage = 0; //Placeholder
}

// Called when the game starts or when spawned
void AEnemy_Basic::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemy_Basic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (dead)
		return;

	if (_pPlayer == NULL)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerChar::StaticClass(), _foundCharacter);
		for (AActor* protag : _foundCharacter)
		{
			_pPlayer = Cast<APlayerChar>(protag);
		}

		return;
	}
	ticks++;
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Looping %i, "), ticks));
	Pathfinder();

	if (_pPlayer->dead)
		return;

	Hit();

}

void AEnemy_Basic::Hit()
{
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
}

void AEnemy_Basic::Pathfinder()
{
	if (_pPathfinder != NULL && ticks > 10)
	{
		_pPathfinder->Reset();

	}
	if (_pPathfinder == NULL)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		_pPathfinder = GetWorld()->SpawnActor<Anewastar>(FVector(1, 1, 1), FRotator(1, 1, 1), SpawnInfo);;
		_pPathfinder->Find(_pPlayer->GetActorLocation(), this->GetActorLocation());
	}

	if (_pPathfinder->path.Num() > minus)
	{

		if (FVector::Distance(_pPathfinder->nodes[_pPathfinder->path[_pPathfinder->path.Num() - minus]].position, this->GetActorLocation()) < 4)
			minus++;

		FVector location = _pPathfinder->nodes[_pPathfinder->path[_pPathfinder->path.Num() - minus]].position;//Pathfinder->nodes[Pathfinder->path[Pathfinder->path.Num() - minus]].position;//next node replace

																											  //GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("looping %i,  %f"), minus, location.X));

		if (location.X >= this->GetActorLocation().X)
		{
			enemySprite->AddLocalOffset(FVector(3, 0, 0), false, NULL, ETeleportType::None);
		}

		if (location.X <= this->GetActorLocation().X)
		{
			enemySprite->AddLocalOffset(FVector(-3, 0, 0), false, NULL, ETeleportType::None);
		}

		if (location.Z >= this->GetActorLocation().Z)
		{
			enemySprite->AddLocalOffset(FVector(0, 0, 3), false, NULL, ETeleportType::None);
		}

		if (location.Z <= this->GetActorLocation().Z)
		{
			enemySprite->AddLocalOffset(FVector(0, 0, -3), false, NULL, ETeleportType::None);
		}


		if (location.X < this->GetActorLocation().X + 4 && location.X > this->GetActorLocation().X - 4 && location.Z < this->GetActorLocation().Z + 4 && location.Z > this->GetActorLocation().Z - 4)
		{
			minus++;
		}
	}
}


//void AEnemy_Basic::Attack()
//{
//	// Transfer attack stuff.
//}



