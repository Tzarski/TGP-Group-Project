// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerChar.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "SpawnRoom.h"
#include "Classes/Particles/ParticleSystem.h"
#include "Enemy_Ghost.h"
#include "Enemy_Splitter.h"
#include "Enemy_SplitterChild.h"
#include "Enemy_Basic.h"
#include "Enemy_Mage.h"
#include "Enemy_Tough.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Sound.h"

// Sets default values
APlayerChar::APlayerChar(const FObjectInitializer& PCIP) : Super(PCIP)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	defaultsprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PlayerSprite"));
	LoadPaperSprites();
	defaultsprite->SetSprite(papersprite[1]);
	defaultsprite->SetupAttachment(RootComponent);
	defaultsprite->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	defaultsprite->SetCollisionProfileName(TEXT("OverlapAll"));

	particle = ConstructorHelpers::FObjectFinder<UParticleSystem>(TEXT("blood'/Game/Blood_attack.Blood_attack'")).Object;
	swordSoundEffect = CreateDefaultSubobject<USound>(TEXT("SwordSound"));
	swordSoundEffect->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("swordsoundeffect'/Game/Audio/Sword_swing.Sword_swing'")).Object);
	swordSoundEffect->LowerVolume(8.0f);

	playerSoundEffect = CreateDefaultSubobject<USound>(TEXT("PlayerSound"));
	playerSoundEffect->SetSound(ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("playerSoundEffect'/Game/Audio/Hurt.Hurt'")).Object);
	playerSoundEffect->LowerVolume(4.0f);

	
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

	GlobalVars->Damage(1);	
	GetWorld()->GetTimerManager().SetTimer(handle1, [this]() {	defaultsprite->SetSpriteColor(FLinearColor(255, 255, 255, 1));}, 2, false);
	playerSoundEffect->PlaySound();
	
	

}
// Called every frame
void APlayerChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//SetSprites();
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
				if (Hit.Actor->GetName().Contains("Ghost", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					Cast<AEnemy_Ghost>(Hit.Actor)->Damaged();
					//DrawDebugSphere(GetWorld(), SweepStart, 20, 5, FColor::Green, true, -1, 0, 10);
					return;
				}
				else if (Hit.Actor->GetName().Contains("Child", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					Cast<AEnemy_SplitterChild>(Hit.Actor)->Damaged();
					//DrawDebugSphere(GetWorld(), SweepStart, 20, 5, FColor::Green, true, -1, 0, 10);
					return;
				}
				else if (Hit.Actor->GetName().Contains("Splitter", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					Cast<AEnemy_Splitter>(Hit.Actor)->Damaged();
					//DrawDebugSphere(GetWorld(), SweepStart, 20, 5, FColor::Green, true, -1, 0, 10);
					return;
				}
				else if (Hit.Actor->GetName().Contains("Basic", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					Cast<AEnemy_Basic>(Hit.Actor)->Damaged();
					//DrawDebugSphere(GetWorld(), SweepStart, 20, 5, FColor::Green, true, -1, 0, 10);
					return;
				}
				else if (Hit.Actor->GetName().Contains("Mage", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					Cast<AEnemy_Mage>(Hit.Actor)->Damaged();
					//DrawDebugSphere(GetWorld(), SweepStart, 20, 5, FColor::Green, true, -1, 0, 10);
					return;
				}
				else if (Hit.Actor->GetName().Contains("Tough", ESearchCase::IgnoreCase, ESearchDir::FromStart))
				{
					Cast<AEnemy_Tough>(Hit.Actor)->Damaged();
					//DrawDebugSphere(GetWorld(), SweepStart, 20, 5, FColor::Green, true, -1, 0, 10);
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
	{
		direction = 3;
		defaultsprite->SetSprite(papersprite[5]);
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("up")));
	}
	else
	{
		direction = 4;
		defaultsprite->SetSprite(papersprite[0]);
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("down")));
	}
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
			defaultsprite->SetSprite(papersprite[2]);
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("left" )));
		defaultflipbook->SetRelativeRotation(FRotator(0 , 0, 0), false, NULL, ETeleportType::None);
		}
		else
		{
			direction = 2; 
			defaultsprite->SetSprite(papersprite[4]);
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
		swordSoundEffect->PlaySound();
	}


}

void APlayerChar::LoadPaperSprites()
{
	papersprite[0] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("defaultsprite'/Game/Art/Gen/character/character_Sprite_0.character_Sprite_0'")).Object;
	papersprite[1] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("defaultsprite'/Game/Art/Gen/character/character_Sprite_1.character_Sprite_1'")).Object;
	papersprite[2] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("defaultsprite'/Game/Art/Gen/character/character_Sprite_2.character_Sprite_2'")).Object;
	papersprite[3] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("defaultsprite'/Game/Art/Gen/character/character_Sprite_3.character_Sprite_3'")).Object;
	papersprite[4] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("defaultsprite'/Game/Art/Gen/character/character_Sprite_4.character_Sprite_4'")).Object;
	papersprite[5] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("defaultsprite'/Game/Art/Gen/character/character_Sprite_5.character_Sprite_5'")).Object;
	papersprite[6] = ConstructorHelpers::FObjectFinder<UPaperSprite>(TEXT("defaultsprite'/Game/Art/Gen/character/character_Sprite_6.character_Sprite_6'")).Object;
}

//void APlayerChar::SetSprites()
//{
//	
//}

// Called to bind functionality to input
void APlayerChar::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("UD", this, &APlayerChar::moveupdown);
	PlayerInputComponent->BindAxis("Attack", this, &APlayerChar::Attack);
	PlayerInputComponent->BindAxis("LR", this, &APlayerChar::moveleftright);
}

