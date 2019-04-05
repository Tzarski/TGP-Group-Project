// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Sound.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API USound : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USound();

	UFUNCTION()
	void PlaySound();

	void LoopSound(bool unlimited, int timesToPlay);
	void StopSound();
	void SetSound(USoundBase* soundSelected);

private:
	class UAudioComponent* soundPlay;
	bool _unlimited = true;
	int _timesToPlay = 0;


protected:	
};
