// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerChar.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "SpawnRoom.h"
#include "Classes/Particles/ParticleSystem.h"
#include "Enemy.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

// Sets default values
APlayerChar::APlayerChar(const FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	defaultsprite = PCIP.CreateDefaultSubobject<UPaperSpriteComponent>(this, TEXT("default sprite"));
	defaultsprite->SetSprite(ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("PaperSprite'/Game/Art/Gen/player_Sprite.player_Sprite'")).Object);

	particle = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("blood'/Game/Blood_attack.Blood_attack'")).Object;
	

	
	defaultflipbook = PCIP.CreateDefaultSubobject<UPaperFlipbookComponent>(this, TEXT("sword flip"));
	defaultflipbook->SetFlipbook(ConstructorHelpers::FObjectFinder<UPaperFlipbook>(TEXT("PaperFlipbook'/Game/Art/Weapons/swordanim.swordanim'")).Object);
	defaultflipbook->SetSpriteColor(FLinearColor(0, 0, 0, 0));
	defaultsprite->SetupAttachment(RootComponent);
	defaultflipbook->SetupAttachment(defaultsprite);
	defaultflipbook->SetRelativeScale3D(FVector(3, 3, 3));
	defaultsprite->SetSpriteColor(FLinearColor(255, 255, 255, 1));
	GetCharacterMovement()->GravityScale = 0;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APlayerChar::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> foundCharacter;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGlobals::StaticClass(), foundCharacter);
	for (AActor* protag : foundCharacter)
	{
		GlobalVars = Cast<AGlobals>(protag);
	}
	
}


void APlayerChar::TakeDamage()
{
	if (dead || GlobalVars->paused)
		return;
	if (defaultsprite->GetSpriteColor() == FLinearColor(255, 0, 0, 1))
		return;

	UGameplayStatics::SpawnEmitterAttached(particle, defaultsprite->GetAttachmentRoot(), NAME_None, FVector(0.0f, 0.1f, -20.0f), FRotator(0.0f, 0.0f, 0.0f), EAttachLocation::Type::SnapToTarget, true);
	defaultsprite->SetSpriteColor(FLinearColor(255, 0, 0, 1));	

	GlobalVars->health--;
	GetWorld()->GetTimerManager().SetTimer(handle1, [this]() {	defaultsprite->SetSpriteColor(FLinearColor(255, 255, 255, 1));}, 2, false);
	
	

}
// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(GetWorld()->GetTimerManager().GetTimerElapsed(handle1) > 2)
		GetWorld()->GetTimerManager().ClearTimer(handle1);
	if(GetWorld()->GetTimerManager().GetTimerElapsed(handle) > 3)
		GetWorld()->GetTimerManager().ClearTimer(handle);
	if (dead || GlobalVars->paused)
		return;
	if (!attacking)
		return;
	TArray<FHitResult> OutHits;
	FVector SweepStart = defaultflipbook->GetComponentLocation();
	FVector SweepEnd = defaultflipbook->GetComponentLocation();
	FCollisionShape MyColSphere = FCollisionShape::MakeSphere(20.0f);
	
	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, SweepStart , SweepEnd , FQuat::Identity, ECC_WorldStatic, MyColSphere);
	bool cantmove = false;

	if (isHit)
	{
		for (auto& Hit : OutHits)
		{
			if (GEngine)
			{
				if (Hit.Actor->GetName().Contains("Enemy", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					Cast<AEnemy>(Hit.Actor)->Hit();
					DrawDebugSphere(GetWorld(), SweepStart, 20, 5, FColor::Green, true, -1, 0, 10);
					return;
				}
			}
		}
	}
}

void APlayerChar::moveupdown(float dir)
{
	if (dead || GlobalVars->paused)
		return;
	if (attacking)
		return;
	if (dir == 0)
		return;
	if (dir > 0)
		direction = 3;
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("up")));
	else
		direction = 4;
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("down")));
	if (!attacking)
	{
		defaultflipbook->SetRelativeRotation(FRotator(90 * dir, 0, 0), false, NULL, ETeleportType::None);
		defaultflipbook->SetRelativeLocation(FVector(0, 0, 60 * dir), false, NULL, ETeleportType::None);
	}
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
	if (dead || GlobalVars->paused)
		return;
	if (attacking)
		return;
	if (dir == 0)		
		return;
	if (!attacking)
	{
		if (dir > 0)
		{
			direction = 1;
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("left" )));
		defaultflipbook->SetRelativeRotation(FRotator(0 , 0, 0), false, NULL, ETeleportType::None);
		}
		else
		{
			direction = 2; 
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("right")));
		defaultflipbook->SetRelativeRotation(FRotator(180, 0, 0), false, NULL, ETeleportType::None);
		}
	defaultflipbook->SetRelativeLocation(FVector(60 * dir, 0, 0), false, NULL, ETeleportType::None);
	}
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
					if(dir == 1)
						Cast<ASpawnRoom>(FoundActors[0])->SpawnRoom(-1);
					else
						Cast<ASpawnRoom>(FoundActors[0])->SpawnRoom(1);
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

void APlayerChar::Attack(float dir)
{
	if (dir == -1)
	{
		GlobalVars->paused = !GlobalVars->paused;
	}
	if (dir != 1)
		return;
	
	if (dead || GlobalVars->paused)
		return;
	if (!attacking)
	{
		attacking = true;
		defaultflipbook->SetSpriteColor(FLinearColor(255,255, 255, 1));
		defaultflipbook->Activate();
		defaultflipbook->Play();
		GetWorld()->GetTimerManager().SetTimer(handle, [this]() {	attacking = false; defaultflipbook->Deactivate(); defaultflipbook->Stop(); 	defaultflipbook->SetSpriteColor(FLinearColor(0, 0, 0, 0)); }, 0.1, false);

	}


}
// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("UD", this, &APlayerChar::moveupdown);
	PlayerInputComponent->BindAxis("Attack", this, &APlayerChar::Attack);
	PlayerInputComponent->BindAxis("LR", this, &APlayerChar::moveleftright);
}

