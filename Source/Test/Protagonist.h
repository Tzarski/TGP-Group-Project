// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Protagonist.generated.h"

UCLASS()
class TEST_API AProtagonist : public APawn
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
		class UStaticMeshComponent* character;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision)
		class UBoxComponent* collision;

	// Sets default values for this pawn's properties
	AProtagonist();
	void MoveForward(float scale);
	void MoveRight(float scale);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
