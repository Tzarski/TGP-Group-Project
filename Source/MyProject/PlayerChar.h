// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
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
	FTimerHandle    handle;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	class UPaperSpriteComponent* defaultsprite;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawn Points")
	AGlobals* GlobalVars;
	void TakeDamage();
	void moveupdown(float dir);
	void moveleftright(float dir);
};
