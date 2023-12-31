// Copyright Epic Games, Inc. All Rights Reserved.
#include "firstProjectGameModeBase.h"
#include "Json/UShopData.h"
AfirstProjectGameModeBase::AfirstProjectGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn> finder(TEXT("/Script/Engine.Blueprint'/Game/Bundle/Character/BPC_Player.BPC_Player_c'"));
	if (finder.Succeeded())
	{
		
		DefaultPawnClass = finder.Class;
	}
	TArray<FUShopData> arrays = FUShopData::UserDataReadJsons();
}

AfirstProjectGameModeBase::~AfirstProjectGameModeBase()
{
}
