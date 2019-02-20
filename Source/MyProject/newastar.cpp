// Fill out your copyright notice in the Description page of Project Settings.


#include "newastar.h"
#include <thread> 

// Sets default values
Anewastar::Anewastar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Anewastar::BeginPlay()
{
	Super::BeginPlay();

	Start();
	//GetWorld()->GetTimerManager().SetTimer(handle, [this]() {	Start(); }, 100, false);

}
void Anewastar::Start()
{

	MapWorld();
	FindClosestToSandE();
	int loops = 1;
	while (!pathfound)
	{
		if (loops > 1000)
			break;
		loops++;
	
		FindNeighbours();
		FindBestNeighbour();
	}
	int next = end;
	for (int is = 0; is < 1000; is++)
	{
		if (next == start)
			break;
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //c++11
		DrawDebugBox(GetWorld(), nodes[next].position, FVector(25, 25, 25), FColor(is * 5, 0, is * 3.5), false, 100, 0, 5);
		next = nodes[next].LastNumber;


	}
}
void Anewastar::FindBestNeighbour()
{
	float bestDist = 9999;
	int bestN;
	for (int i : neighbours)
	{
		float DistToC = FVector::Dist(nodes[current].position, nodes[i].position);
		float DistToE = FVector::Dist(nodes[end].position, nodes[i].position);
		float DistToS = FVector::Dist(nodes[start].position, nodes[i].position);
		if (DistToC + DistToE  <= bestDist)
		{
			bestDist = DistToC + DistToE;
			bestN = i;
		}
	}
	if (bestN == end)
	{
		nodes[end].LastNumber = bestN;
		pathfound = true;
	}
	nodes[bestN].LastNumber = current;
	neighbours.Remove(bestN);
	current = bestN;
}
void Anewastar::FindNeighbours()
{
	FASNode currentN = nodes[current];
	int f = 0;
	if (nodes.Find(FASNode(currentN.position.X + 50, currentN.position.Z, 0), f))
	{
		if(!nodes[f].isClosed)
		{
			nodes[f].isClosed = true;
			neighbours.Add(f);
		//	DrawDebugBox(GetWorld(), nodes[f].position, FVector(50, 50, 50), FColor(f,f * 1.5,0), false, 100, 0, 5);
		}
	}
	if (nodes.Find(FASNode(currentN.position.X - 50, currentN.position.Z, 0), f))
	{
		if (!nodes[f].isClosed)
		{
			nodes[f].isClosed = true;
			neighbours.Add(f);
			//DrawDebugBox(GetWorld(), nodes[f].position, FVector(50, 50, 50), FColor(f, f * 1.5, 0), false, 100, 0, 5);

		}
		
	}
	if (nodes.Find(FASNode(currentN.position.X , currentN.position.Z + 50, 0), f))
	{
		if (!nodes[f].isClosed)
		{
			nodes[f].isClosed = true;
			neighbours.Add(f);
	//	DrawDebugBox(GetWorld(), nodes[f].position, FVector(50, 50, 50), FColor(f, f * 1.5, 0), false, 100, 0, 5);
		}
		
	}
	if (nodes.Find(FASNode(currentN.position.X,  currentN.position.Z - 50, 0), f))
	{
		if (!nodes[f].isClosed)
		{
			nodes[f].isClosed = true;
			neighbours.Add(f);
			//DrawDebugBox(GetWorld(), nodes[f].position, FVector(50, 50, 50), FColor(f, f * 1.5, 0), false, 100, 0, 5);
		}
		
	}

}
void Anewastar::FindClosestToSandE()
{
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
	
	for (FASNode node : nodes)
	{
		if (FVector::Distance(node.position, player->GetActorLocation()) < FDistance)
		{
			start = node.MyNumber;
			FDistance = FVector::Distance(node.position, player->GetActorLocation());
		}
	}

	int EDistance = 99999;

	for (FASNode node : nodes)
	{
		if (FVector::Distance(node.position, enemy->GetActorLocation()) < EDistance)
		{
			end = node.MyNumber;
			EDistance = FVector::Distance(node.position, enemy->GetActorLocation());
		}
	}

	current = start;
	nodes[start].start = true;
	nodes[end].end = true;
	DrawDebugBox(GetWorld(), nodes[start].position, FVector(50, 50, 50), FColor::Orange, false, 100, 0, 5);
	DrawDebugBox(GetWorld(), nodes[end].position, FVector(50, 50, 50), FColor::Orange, false, 100, 0, 5);
}
void Anewastar::MapWorld()
{
	int loop = 0;

	for (int i = 0; i < 50; i++)
	{
		for (int f = 0; f < 25; f++)
		{
			TArray<FHitResult> OutHits;
			FVector SweepStart = FVector(i * 50, 0, -f * 50);
			FCollisionShape MyColCube = FCollisionShape::MakeBox(FVector(50, 50, 50));
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

				nodes.Add(FASNode(i * 50, -f * 50, loop));
				loop++;
				//DrawDebugBox(GetWorld(), SweepStart, FVector(50, 50, 50), FColor::Orange, false, 100, 0, 1);
				continue;
			}
			else if (!gothit && gothit2)
			{
				//DrawDebugBox(GetWorld(), SweepStart, FVector(50, 50, 50), FColor::Purple, false, 100, 0, 1);
				continue;

			}
			else if (gothit2)
			{
				//	DrawDebugBox(GetWorld(), SweepStart, FVector(50, 50, 50), FColor::Blue, false, 100, 0, 1);
				continue;
			}


		}
	}
}
// Called every frame
void Anewastar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

