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
//
//

//
// Called // frame
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
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Looping %i, "), ticks));

	//Pathfinder();

	Move();

	SetSprites();

	if (_pPlayer->dead)
		return;

	Hit();

}

void AEnemy_Base::Hit()
{
	TArray<FHitResult> OutHits;
	FVector SweepStart = GetActorLocation();
	FVector SweepEnd = GetActorLocation();
	FCollisionShape MyColSphere = FCollisionShape::MakeBox(FVector(32, 10.0f, 32));

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
	
}

void AEnemy_Base::Move()
{
	

		FVector location = _pPlayer->GetActorLocation(); 

		if (location.X >= this->GetActorLocation().X)
		{
			enemySprite->AddLocalOffset(FVector(3, 0, 0), true, NULL, ETeleportType::None);
		}

		if (location.X <= this->GetActorLocation().X)
		{
			enemySprite->AddLocalOffset(FVector(-3, 0, 0), true, NULL, ETeleportType::None);
		}

		if (location.Z >= this->GetActorLocation().Z)
		{
			enemySprite->AddLocalOffset(FVector(0, 0, 3), true, NULL, ETeleportType::None);
		}

		if (location.Z <= this->GetActorLocation().Z)
		{
			enemySprite->AddLocalOffset(FVector(0, 0, -3), true, NULL, ETeleportType::None);
		}


}

void AEnemy_Base::SetSprites()
{

}
