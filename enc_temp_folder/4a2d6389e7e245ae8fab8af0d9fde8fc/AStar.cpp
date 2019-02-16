// Fill out your copyright notice in the Description page of Project Settings.

#include "AStar.h"
#include "PlayerChar.h"
#include "Enemy.h" 

// Sets default values
AAStar::AAStar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	size = 25;
}

// Called when the game starts or when spawned
void AAStar::BeginPlay()
{
	Super::BeginPlay();
	
	int f = 0;
	int loop = 0;
	while (f < 30)
	{
		for (int i = 0; i < 100; i++)
		{
			loop++;
			TestSquare(i * size, 1, -f * size, loop);
				
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
	int current = start.myNumber;
	if ((current + 1) < (basiclist.Num() - 1) && CanWalkList.Contains(basiclist[current + 1].position))
	{
		if (basiclist[current + 1].walkable && !searched.Contains(basiclist[current + 1].myNumber))
		{
			DrawDebugBox(GetWorld(), basiclist[current + 1].position, FVector(25, 25, 25), FColor::Green, false, 100, 0, 5);
			searched.Add(basiclist[current + 1].myNumber);
			neighbours.Add(basiclist[current + 1].myNumber);
			CanWalkList.Remove(basiclist[current + 1]);
		}
	}
	if ((current - 1) >= 0 && CanWalkList.Contains(basiclist[current - 1].position))
	{
		if (basiclist[current - 1].walkable && !searched.Contains(basiclist[current - 1].myNumber))
		{
			searched.Add(basiclist[current - 1].myNumber);
			DrawDebugBox(GetWorld(), basiclist[current - 1].position, FVector(25, 25, 25), FColor::Green, false, 100, 0, 5);
			//	DrawDebugBox(GetWorld(), basiclist[current - 1].position, FVector(50, 50, 50), FColor(loops * 10, 0, 0, 1), false, 100, 0, 10);
			neighbours.Add(basiclist[current - 1].myNumber);
			CanWalkList.Remove(basiclist[current - 1]);
		}
	}
	int dumb = 100;
	if ((current + dumb) < (basiclist.Num() - 1) && CanWalkList.Contains(basiclist[current + dumb].position))
	{
		if (basiclist[current + dumb].walkable && !searched.Contains(basiclist[current + dumb].myNumber))
		{
			searched.Add(basiclist[current + dumb].myNumber);
				DrawDebugBox(GetWorld(), basiclist[current + dumb].position, FVector(25, 25, 25), FColor::Green, false, 100, 0, 5);
			
			neighbours.Add(basiclist[current + dumb].myNumber);
			CanWalkList.Remove(basiclist[current + dumb]);
		}
		//	else
		//	DrawDebugBox(GetWorld(), basiclist[current + dumb].position, FVector(25, 25, 25), FColor::Red, false, 100, 0, 5);
	}
	if ((current - dumb) >= 0 && CanWalkList.Contains(basiclist[current - dumb].position))
	{
		if (basiclist[current - dumb].walkable && !searched.Contains(basiclist[current - dumb].myNumber))
		{
			searched.Add(basiclist[current - dumb].myNumber);
			DrawDebugBox(GetWorld(), basiclist[current - dumb].position, FVector(25, 25, 25), FColor::Green, false, 100, 0, 5);
			neighbours.Add(basiclist[current - dumb].myNumber);
			CanWalkList.Remove(basiclist[current - dumb]);
		}
		//else
		//	DrawDebugBox(GetWorld(), basiclist[current - dumb].position, FVector(25, 25, 25), FColor::Red, false, 100, 0, 5);
	}


	bool pathfound = false;
	int loops = 0;
	int bestneighbour = current;
	GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("sasas %i, %i, %i, %i, %i"), bestneighbour, loops, bestneighbour, current, end.lastpos));
	while (!pathfound)
	{
		loops++;
		if (loops > 2222)
			break;
		int FDistance = 99999;
		int loopes = 0;
		bestneighbour = 0;

		for (int currents : neighbours)
		{
			loopes++;
			int CDistance = FVector::Distance(basiclist[currents].position, end.position) + FVector::Distance(basiclist[currents].position, start.position);
			if (CDistance <= FDistance)
			{
				
				bestneighbour = currents;
				FDistance = CDistance;
				
			}
		}
		distancesofar++;
		basiclist[bestneighbour].lastpos = current;
		neighbours.Remove(bestneighbour);

		
		if (bestneighbour == end.myNumber)
		{
		
			end.lastpos = current;
			GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("looping?")));
			
			pathfound = true;
			break;
		}
		
		current = bestneighbour;
		
		
		
	
		if ((current + 1) < (basiclist.Num() - 1) && CanWalkList.Contains(basiclist[current + 1].position))
		{
			if (basiclist[current + 1].walkable && !searched.Contains(basiclist[current + 1].myNumber))
			{
				searched.Add(basiclist[current + 1].myNumber);
				DrawDebugBox(GetWorld(), basiclist[current + 1].position, FVector(50, 50, 50), FColor::Green, false, 100, 0, 10);
				neighbours.Add(basiclist[current + 1].myNumber);
				CanWalkList.Remove(basiclist[current + 1]);
			}else
				DrawDebugBox(GetWorld(), basiclist[current + 1].position, FVector(50, 50, 50), FColor::Red, false, 100, 0, 10);
		}
		if ((current - 1) >= 0 && CanWalkList.Contains(basiclist[current - 1].position))
		{
			if (basiclist[current - 1].walkable && !searched.Contains(basiclist[current - 1].myNumber))
			{
				searched.Add(basiclist[current - 1].myNumber);
				DrawDebugBox(GetWorld(), basiclist[current - 1].position, FVector(50, 50, 50), FColor::Green , false, 100, 0, 10);
				neighbours.Add(basiclist[current - 1].myNumber);
				CanWalkList.Remove(basiclist[current - 1]);
			}else
				DrawDebugBox(GetWorld(), basiclist[current - 1].position, FVector(50, 50, 50), FColor::Red, false, 100, 0, 10);
		}
		if ((current + dumb) < (basiclist.Num() - 1) && CanWalkList.Contains(basiclist[current + dumb].position))
		{
			if (basiclist[current + dumb].walkable && !searched.Contains(basiclist[current + dumb].myNumber))
			{
				searched.Add(basiclist[current + dumb].myNumber);
				DrawDebugBox(GetWorld(), basiclist[current + dumb].position, FVector(25, 25, 25), FColor::Green, false, 100, 0, 5);
				neighbours.Add(basiclist[current + dumb].myNumber);
				CanWalkList.Remove(basiclist[current + dumb]);
			}
			else
				DrawDebugBox(GetWorld(), basiclist[current + dumb].position, FVector(25, 25, 25), FColor::Red, false, 100, 0, 5);
		}
		if ((current - dumb) >= 0 && CanWalkList.Contains(basiclist[current - dumb].position))
		{
			if (basiclist[current - dumb].walkable && !searched.Contains(basiclist[current - dumb].myNumber))
			{
				searched.Add(basiclist[current - dumb].myNumber);
				DrawDebugBox(GetWorld(), basiclist[current - dumb].position, FVector(25, 25, 25), FColor::Green, false, 100, 0, 5);
				neighbours.Add(basiclist[current - dumb].myNumber);
				CanWalkList.Remove(basiclist[current - dumb]);
			}
			else
				DrawDebugBox(GetWorld(), basiclist[current - dumb].position, FVector(25, 25, 25), FColor::Red, false, 100, 0, 5);
		}



	}
	//
	//return;
	FNodes posA = FNodes();
	posA = basiclist[bestneighbour];
	int next;
	next = basiclist[bestneighbour].lastpos;
	loops = 0;

	
	while (posA.myNumber != start.myNumber)
	{
	
		loops++;
		if (loops > 20)
			return;
	//	DrawDebugBox(GetWorld(), posA.position, FVector(50, 50, 50), FColor(loops * 10, 0, 0, 1), false, 100, 0, 10);
		
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, FString::Printf(TEXT("sas %i, %i, %i, %i, %i"), next, loops, posA.lastpos, posA.myNumber, end.lastpos));
		
		

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
	CanWalkList.Add(FNodes(SweepStart, loop));
	/*
	if (gothit && !gothit2)
		DrawDebugBox(GetWorld(), SweepStart, FVector(25, 25, 25), FColor::Green, false, 100, 0, 1);
	else
		DrawDebugBox(GetWorld(), SweepStart, FVector(25, 25, 25), FColor::Red, false, 100, 0, 1);
		*/
	if (gothit && !gothit2)
	{
		
		CanWalkList[loop -1 ].walkable = true;
		return true;
	}
	return false;
}
// Called every frame
void AAStar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

