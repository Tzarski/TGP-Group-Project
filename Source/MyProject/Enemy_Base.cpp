// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Base.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UnrealType.h"

// Sets default values
AEnemy_Base::AEnemy_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (dead)
		return;
	//return;//remove this just testing the a*
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
	Move();
	SetSprites();
	/*if (_pPathfinder != NULL && ticks > 10)
	{
		_pPathfinder->Reset();

	}
	if (_pPathfinder == NULL)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		_pPathfinder = GetWorld()->SpawnActor<Anewastar>(FVector(1, 1, 1), FRotator(1, 1, 1), SpawnInfo);;
		_pPathfinder->Find(_pPlayer->GetActorLocation(), this->GetActorLocation());
	}*/


	if (_pPlayer->dead)
		return;
	//DrawDebugSphere(GetWorld(), this->GetActorLocation(), 70, 70, FColor::Red, true, 2, 0, 10);

	//TArray<FHitResult> OutHits;
	//FVector SweepStart = this->GetActorLocation();
	//FVector SweepEnd = this->GetActorLocation();
	//FCollisionShape MyColSphere = FCollisionShape::MakeSphere(70.0f);

	//bool isHit = GetWorld()->SweepMultiByChannel(OutHits, SweepStart, SweepEnd, FQuat::Identity, ECC_WorldStatic, MyColSphere);
	//bool cantmove = false;

	//if (isHit)
	//{
	//	for (auto& Hit : OutHits)
	//	{
	//		if (GEngine)
	//		{
	//			if (Hit.Actor->GetName().Contains("player", ESearchCase::IgnoreCase, ESearchDir::FromStart))
	//			{
	//				Cast<APlayerChar>(Hit.Actor)->TakeDamage();

	//				return;
	//			}
	//		}
	//	}
	//}
	Hit();

}

void AEnemy_Base::Hit()
{
	TArray<FHitResult> OutHits;
	FVector SweepStart = GetActorLocation();
	FVector SweepEnd = GetActorLocation();
	FCollisionShape MyColSphere = FCollisionShape::MakeBox(FVector(enemySprite->GetSprite()->GetSourceSize().X/2, 10.0f, enemySprite->GetSprite()->GetSourceSize().Y/2));

	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, SweepStart, SweepEnd, FQuat::Identity, ECC_WorldStatic, MyColSphere);
	block = attacking = false;

	if (isHit)
	{
		for (auto& Hit : OutHits)
		{
			if (GEngine)
			{
				if (Hit.Component->GetName().Contains("player", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					Cast<APlayerChar>(Hit.Actor)->TakeDamage();
					attacking = true;
					return;
				}
				if (Hit.Component->GetName().Contains("wall", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					block = true;
					return;
				}
			}
		}
	}
}

//void AEnemy_Base::Attack()
//{
//	// Transfer attack stuff.
//}

void AEnemy_Base::Pathfinder()
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

	
}

void AEnemy_Base::Move()
{
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

void AEnemy_Base::SetSprites()
{
}
