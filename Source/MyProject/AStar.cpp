// Fill out your copyright notice in the Description page of Project Settings.

#include "AStar.h"
#include "PlayerChar.h"
#include "Enemy.h" 

// Sets default values
AAStar::AAStar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAStar::BeginPlay()
{
	Super::BeginPlay();
	
	int f = 0;
	while (f < 30)
	{
		for (int i = 0; i < 100; i++)
		{
			TestSquare(i * 25, 1, -f * 25);
		}
		f++;
	}
	TArray<AActor*> foundCharacter;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerChar::StaticClass(), foundCharacter);
	for (AActor* protag : foundCharacter)
	{
		player = Cast<APlayerChar>(protag);
	}
	foundCharacter.Empty();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), foundCharacter);
	for (AActor* protag : foundCharacter)
	{
		enemy = Cast<AEnemy>(protag);
	}
	int FDistance = 99999;
	FVector start = FVector(1,1,1);
	for (FVector position : CanWalkList)
	{
		if (FVector::Distance(position, player->GetActorLocation()) < FDistance)
		{
			start = position;
			FDistance = FVector::Distance(position, player->GetActorLocation());
		}
	}

	int EDistance = 99999;
	FVector end = FVector(1, 1, 1);
	for (FVector position : CanWalkList)
	{
		if (FVector::Distance(position, enemy->GetActorLocation()) < EDistance)
		{
			end = position;
			EDistance = FVector::Distance(position, enemy->GetActorLocation());
		}
	}
	CanWalkList.Remove(start);
	//CanWalkList.Remove(end);
	int distancesofar = 1;
	DrawDebugBox(GetWorld(), start, FVector(25, 25, 25), FColor::Purple, false, 100, 0, 10);
	DrawDebugBox(GetWorld(), end, FVector(25, 25, 25), FColor::Orange, false, 100, 0, 10);
	FVector current = start;
	if (CanWalkList.Contains(current + FVector(25, 0, 0)))
		neighbours.Add(current + FVector(25, 0, 0));
	if (CanWalkList.Contains(current + FVector(-25, 0, 0)))
		neighbours.Add(current + FVector(-25, 0, 0));
	if (CanWalkList.Contains(current + FVector(0, 0, 25)))
		neighbours.Add(current + FVector(0, 0, 25));
	if (CanWalkList.Contains(current + FVector(0, 0, -25)))
		neighbours.Add(current + FVector(0, 0, -25));
	bool pathfound = false;
	int loops = 0;
	FVector bestneighbour = current;

	while (!pathfound)
	{
		loops++;
		if (loops > 1000)
			break;
		int FDistance = 99999;
		for (FVector currents : neighbours)
		{
			int CDistance = FVector::Distance(currents, end) + FVector::Distance(currents, start) + distancesofar;
			if (CDistance < FDistance)
			{
				bestneighbour = currents;
				FDistance = CDistance;
			}
		}
		distancesofar++;
		allpossible.Add(FNodes(bestneighbour,current, allpossible.Num() - 1));
		neighbours.Remove(bestneighbour);
	
		current = bestneighbour;
		if (current == end)
		{
			pathfound = true;
		}
		CanWalkList.Remove(current);

	if(CanWalkList.Contains(current + FVector(25, 0, 0)) && !neighbours.Contains(current + FVector(25, 0, 0)) )
		neighbours.Add( current + FVector(25, 0, 0));
	if (CanWalkList.Contains(current + FVector(-25, 0, 0)) && !neighbours.Contains(current + FVector(25, 0, 0)))
		neighbours.Add( current + FVector(-25, 0, 0));
	if (CanWalkList.Contains(current + FVector(0, 0, 25)) && !neighbours.Contains(current + FVector(25, 0, 0)))
		neighbours.Add( current + FVector(0, 0, 25));
	if (CanWalkList.Contains(current + FVector(0, 0, -25)) && !neighbours.Contains(current + FVector(25, 0, 0)))
		neighbours.Add( current + FVector(0, 0, -25));
	}

	FVector posA = FVector(1, 1, 1);
	posA = allpossible[allpossible.Num() - 1].position;
	int next;
	next = allpossible[allpossible.Num() - 1].lastpos;
	loops = 0;
	while (posA != start)
	{
		loops++;
		if (loops > 20)
			break;
		posA = allpossible[next].position;
		next = allpossible[next].lastpos;
		DrawDebugBox(GetWorld(), posA, FVector(25, 25, 25), FColor::Green, false, 100, 0, 10);
	}
	
	



}

void AAStar::TestSquare(float x, float y, float z)
{
	TArray<FHitResult> OutHits;
	FVector SweepStart = FVector(x,y,z);
	FCollisionShape MyColCube = FCollisionShape::MakeBox(FVector(25, 25, 25));
	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, SweepStart, SweepStart, FQuat::Identity, ECC_WorldStatic, MyColCube);
	bool gothit = false;
	bool gothit2 = false;
	if (isHit)
	{
		for (auto& Hit : OutHits)
		{
			if (GEngine)
			{
				if (Hit.Actor->GetName().Contains("floor", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					gothit = true;
					continue;
				}
				if (Hit.Actor->GetName().Contains("roof", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					gothit2 = true;
					continue;
				}
			}
		}
	}
	if (gothit && !gothit2)
		CanWalkList.Add(SweepStart);

}
// Called every frame
void AAStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

