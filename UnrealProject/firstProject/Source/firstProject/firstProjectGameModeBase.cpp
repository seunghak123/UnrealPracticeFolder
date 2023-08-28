// Copyright Epic Games, Inc. All Rights Reserved.
#include "firstProjectGameModeBase.h"

AfirstProjectGameModeBase::AfirstProjectGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn> finder(TEXT("/Script/Engine.Blueprint'/Game/Bundle/Character/BPC_Player.BPC_Player_C'"));
	if (finder.Succeeded())
	{
		
		DefaultPawnClass = finder.Class;
	}
}

AfirstProjectGameModeBase::~AfirstProjectGameModeBase()
{
}
