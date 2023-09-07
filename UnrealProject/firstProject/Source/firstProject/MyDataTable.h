// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MyDataTable.generated.h"

/**
 * 
 */
UCLASS()
class UMyDataTable : public UDataTable
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FurnitureData)
	int index;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FurnitureData)
	int shop_id;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FurnitureData)
	int shop_price;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FurnitureData)
	FString shop_id_string;
};
USTRUCT(BlueprintType)
struct FMyDataTableStruct : public FTableRowBase
{
	//GENERATED_USTRUCT_BODY();
	GENERATED_BODY()
};