// Fill out your copyright notice in the Description page of Project Settings.

#include "AStar.h"
#include "PlayerChar.h"
#include "Enemy.h" 

// Sets default values
AAStar::AAStar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	size = 50;
}

// Called when the game starts or when spawned
void AAStar::BeginPlay()
{
	Super::BeginPlay();
	
	int f = 0;
	int loop = 0;
	while (f < 15)
	{
		for (int i = 0; i < 50; i++)
		{
			
			if( TestSquare(i * size, 1, -f * size, loop))
				loop++;
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
	FNodes start = FNodes();
	for (FNodes node : CanWalkList)
	{
		if (FVector::Distance(node.position, player->GetActorLocation()) < FDistance)
		{
			start = node;
			FDistance = FVector::Distance(node.position, player->GetActorLocation());
		}
	}

	int EDistance = 99999;
	FNodes end = FNodes();
	for (FNodes node : CanWalkList)
	{
		if (FVector::Distance(node.position, enemy->GetActorLocation()) < EDistance)
		{
			end = node;
			EDistance = FVector::Distance(node.position, enemy->GetActorLocation());
		}
	}
	basiclist = CanWalkList;
	GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Green, FString::Printf(TEXT("looping %i, %i"), basiclist.Num(), CanWalkList.Num()));
	int distancesofar = 1;
	//DrawDebugBox(GetWorld(), start.position, FVector(size, size, size), FColor::Purple, false, 100, 0, 10);
	//DrawDebugBox(GetWorld(), end.position, FVector(size, size, size), FColor::Orange, false, 100, 0, 10);
	FNodes current = start;
	
	if (CanWalkList.Contains(current.position + FVector(size, 0, 0)))
		neighbours.Add(FNodes(current.position + FVector(size, 0, 0), current.position + FVector(0, 0, -size), current.myNumber, CanWalkList.Find(FNodes(current.position + FVector(size, 0, 0)))));
	if (CanWalkList.Contains(current.position + FVector(-size, 0, 0)))
		neighbours.Add(FNodes(current.position + FVector(-size, 0, 0), current.position + FVector(0, 0, -size), current.myNumber, CanWalkList.Find(FNodes(current.position + FVector(-size, 0, 0)))));
	if (CanWalkList.Contains(current.position + FVector(0, 0, size)))
		neighbours.Add(FNodes(current.position + FVector(0, 0, size), current.position + FVector(0, 0, -size), current.myNumber, CanWalkList.Find(FNodes(current.position + FVector(0, 0, size)))));
	if (CanWalkList.Contains(current.position + FVector(0, 0, -size)))
		neighbours.Add(FNodes(current.position + FVector(0, 0, -size), current.position + FVector(0, 0, -size), current.myNumber, CanWalkList.Find(FNodes(current.position + FVector(0, 0, -size)))));
	bool pathfound = false;
	int loops = 0;
	FNodes bestneighbour = current;
	
	while (!pathfound)
	{
		loops++;
		if (loops > 3)
			break;
		int FDistance = 99999;
		for (FNodes currents : neighbours)
		{
			int CDistance = FVector::Distance(currents.position, end.position) + FVector::Distance(currents.position, start.position) + (distancesofar * 5);
			if (CDistance < FDistance)
			{
				bestneighbour = currents;
				FDistance = CDistance;
			}
		}
		distancesofar++;
		basiclist[basiclist.Find(FNodes(bestneighbour.position))].lastpos = current.myNumber;
		end.lastpos = current.myNumber;
		//neighbours.Remove(bestneighbour);
	
		current = bestneighbour;
		if (current.position == end.position)
		{
			pathfound = true;
			break;
		}
		CanWalkList.Remove(current);
		if (CanWalkList.Contains(current.position + FVector(size, 0, 0)) && !neighbours.Contains(current.position + FVector(size, 0, 0)))
			neighbours.Add(basiclist[basiclist.Find(FNodes(current.position + FVector(size, 0, 0)))] );
		if (CanWalkList.Contains(current.position + FVector(-size, 0, 0)) && !neighbours.Contains(current.position + FVector(size, 0, 0)))
			neighbours.Add(basiclist[basiclist.Find(FNodes(current.position + FVector(-size, 0, 0)))]);
		if (CanWalkList.Contains(current.position + FVector(0, 0, size)) && !neighbours.Contains(current.position + FVector(size, 0, 0)))
			neighbours.Add(basiclist[basiclist.Find(FNodes(current.position + FVector(0, 0, size)))]);
		if (CanWalkList.Contains(current.position + FVector(0, 0, -size)) && !neighbours.Contains(current.position + FVector(size, 0, 0)))
			neighbours.Add(basiclist[basiclist.Find(FNodes(current.position + FVector(0, 0, -size)))]);





	}
	//
	//return;
	FNodes posA = FNodes();
	posA = end;
	int next;
	next = end.lastpos;
	loops = 0;
	/*for (FNodes node : allpossible)
	{
		DrawDebugBox(GetWorld(), node.position, FVector(size, size, size), FColor(loops, 0, 0, 1), false, 100, 0, 10);
	}*/
	//GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("looping %i, %i, %i"), posA.lastpos, posA.myNumber, start.myNumber));
	while (posA.myNumber != start.myNumber)
	{
	
		loops++;
		if (loops > 100)
			return;
		DrawDebugBox(GetWorld(), posA.position, FVector(50, 50, 50), FColor(loops * 10, 0, 0, 1), false, 100, 0, 10);
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("looping %i, %i, %i, %i, %i"), pathfound ? 1 : 2, loop, posA.lastpos, posA.myNumber, start.myNumber));

		posA = basiclist[next];
		next = basiclist[next].lastpos;
		
		
	}
	
	
	


}

bool AAStar::TestSquare(float x, float y, float z, int loop)
{
	TArray<FHitResult> OutHits;
	FVector SweepStart = FVector(x,y,z);
	FCollisionShape MyColCube = FCollisionShape::MakeBox(FVector(size, size, size));
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
	{
		CanWalkList.Add(FNodes(SweepStart, loop));
		return true;
	}
	return false;
}
// Called every frame
void AAStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

