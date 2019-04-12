// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperFlipbook.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperFlipbookComponent.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSprite.h"
#include "../Plugins/2D/Paper2D/Source/Paper2D/Classes/PaperSpriteComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Globals.h"
#include "DrawDebugHelpers.h"
#include "PlayerChar.generated.h"

UCLASS()
class MYPROJECT_API APlayerChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerChar(const FObjectInitializer& PCIP);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	int direction;//1 = left// 2 = right//3 = up// 4 = down
	FTimerHandle    handle;
	FTimerHandle    handle1;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	class UPaperSpriteComponent* defaultsprite;
	class UPaperFlipbookComponent* defaultflipbook;
	class USound* swordSoundEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawn Points")
		AGlobals* GlobalVars;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Blood_particle")
	class UParticleSystem* particle;

	void TakeDamage();
	void moveupdown(float dir);
	void moveleftright(float dir);
	void Attack(float dir);
	bool attacking;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawn Points")
		bool dead;
};
