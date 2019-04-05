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
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawn Points")
	int health = 2;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawn Points")
	bool paused;

	TArray<AActor*> ExtraToClear;
	
};
