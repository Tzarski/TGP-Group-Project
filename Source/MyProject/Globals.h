// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Globals.generated.h"

UCLASS()
class MYPROJECT_API AGlobals : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlobals();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	int maxhealth = 3;
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "player health")
	int health = 2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Game paused")
	bool paused;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "player health")
		void Heal(int amount);
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "player health")
		void Damage(int amount);

	
};
