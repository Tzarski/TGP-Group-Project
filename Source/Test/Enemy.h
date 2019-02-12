// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class TEST_API AEnemy : public APawn
{
	GENERATED_BODY()

	class AProtagonist* protagonist;
	TArray<AActor*> foundCharacter;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		class UStaticMeshComponent* enemy;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision)
		class UBoxComponent* enemyCollision;

	


	// Sets default values for this pawn's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
