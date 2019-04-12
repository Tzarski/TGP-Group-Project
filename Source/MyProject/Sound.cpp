// Fill out your copyright notice in the Description page of Project Settings.

#include "Sound.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "ConstructorHelpers.h"

// Sets default values for this component's properties
USound::USound()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;


	soundPlay = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio_Settings"));
	soundPlay->bAutoActivate = false;

	// ...
}


// Called when the game starts

void USound::PlaySound()
{
	soundPlay->Play();
	if (!_unlimited)
	{
		LoopSound(_unlimited, _timesToPlay - 1);
	}
}

void USound::LoopSound(bool unlimited, int timesToPlay)
{	
	_unlimited = unlimited;
	_timesToPlay = timesToPlay;	

	if (_timesToPlay > 0 || _unlimited)
	{
		if (!soundPlay->IsPlaying())
		{
			soundPlay->Play();
			_timesToPlay--;
		}
		if (!soundPlay->OnAudioFinished.IsBound())
		soundPlay->OnAudioFinished.AddDynamic(this, &USound::PlaySound);
	}
	if (_timesToPlay <= 0 && !_unlimited)
		soundPlay->OnAudioFinished.Clear();
}



void USound::StopSound()
{
	soundPlay->Stop();
}

void USound::SetSound(USoundBase* soundSelected)
{
	soundPlay->SetSound(soundSelected);
}

void USound::LowerVolume(float lower)
{
	soundPlay->SetVolumeMultiplier(1.0f/lower);
}