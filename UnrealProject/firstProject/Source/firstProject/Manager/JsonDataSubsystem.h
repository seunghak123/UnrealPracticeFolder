// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "JsonDataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPROJECT_API UJsonDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	template <typename T>
	static TArray<T*> LoadJsonData()
	{
		TArray<T*> returnValue;

		UMyDataTable* ItemDataTable = LoadObject<UMyDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/Bundle/Json/JShop.JShop_C'"));
		if (!ItemDataTable)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Failed to load DataTable."));
			//return;
		}
		//LoadObject<UMyDataTable>()
		static ConstructorHelpers::FObjectFinder<UMyDataTable> DataTable(TEXT("/Script/Engine.DataTable'/Game/Bundle/Json/JShop.JShop_c'"));

		if (DataTable.Succeeded())
		{
			UMyDataTable* dataTable = DataTable.Object;

			TArray<T*> arr;
			dataTable->GetAllRows<T>(TEXT("GetAllRows"), arr);

			returnValue = arr;
		}

		return returnValue;
	}
};
