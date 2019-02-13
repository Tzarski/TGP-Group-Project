// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerChar.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "SpawnRoom.h"
// Sets default values
APlayerChar::APlayerChar(const FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	defaultsprite = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("default sprite"));
	defaultsprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Art/Gen/player_Sprite.player_Sprite'")).Object);
	defaultsprite->SetupAttachment(RootComponent);
	GetCharacterMovement()->GravityScale = 0;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(10, 5.f, FColor::Red, FString::Printf(TEXT("char ")));
}

// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerChar::moveupdown(float dir)
{
	if (dir == 0)
		return;

	TArray<FHitResult> OutHits;
	FVector SweepStart = GetActorLocation();
	FVector SweepEnd = GetActorLocation();
	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(5.0f);
	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, SweepStart + FVector(0, 0, 60 * dir), SweepEnd + FVector(0, 0, 60 * dir), FQuat::Identity, ECC_WorldStatic, MyColSphere);
	bool cantmove = false;
	
	if (isHit)
	{
		for (auto& Hit : OutHits)
		{
			if (GEngine)
			{
				if (Hit.Actor->GetName().Contains("roof", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					cantmove = true;
					return;
				}
				if (Hit.Actor->GetName().Contains("door", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					TArray<AActor*> FoundActors;
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnRoom::StaticClass(), FoundActors);
					Cast<ASpawnRoom>(FoundActors[0])->SpawnRoom(2);
					
					cantmove = true;
					return;
				}
			}
		}
	}
	if (cantmove)
		return;
	this->SetActorLocation( FVector(this->GetActorLocation().X , this->GetActorLocation().Y, this->GetActorLocation().Z + 8 * dir));
}
void APlayerChar::moveleftright(float dir)
{
	if (dir == 0)
		return;
	TArray<FHitResult> OutHits;
	FVector SweepStart = GetActorLocation();
	FVector SweepEnd = GetActorLocation();
	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(5.0f);
	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, SweepStart + FVector(60 * dir, 0,0), SweepEnd + FVector(60 * dir, 0, 0), FQuat::Identity, ECC_WorldStatic, MyColSphere);
	bool cantmove = false;

	if (isHit)
	{
		for (auto& Hit : OutHits)
		{
			if (GEngine)
			{
				if (Hit.Actor->GetName().Contains("roof", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{ 
					cantmove = true;
					return;
				}
				if (Hit.Actor->GetName().Contains("door", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					TArray<AActor*> FoundActors;
					UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnRoom::StaticClass(), FoundActors);
					Cast<ASpawnRoom>(FoundActors[0])->SpawnRoom(2);
					cantmove = true;
					return;
				}
			}
		}
	}
	if (cantmove)
		return;
	this->SetActorLocation(FVector(this->GetActorLocation().X + 8 * dir, this->GetActorLocation().Y, this->GetActorLocation().Z ));
}
// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("UD", this, &APlayerChar::moveupdown);
	PlayerInputComponent->BindAxis("LR", this, &APlayerChar::moveleftright);
}

