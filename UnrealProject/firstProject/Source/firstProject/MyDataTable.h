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
};
USTRUCT(BlueprintType)
struct FMyDataTableStruct : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ShopData")
	int index;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ShopData")
	int shop_id;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ShopData")
	int shop_price;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ShopData")
	FString shop_id_string;
public:
	template <typename T>
	TArray<T> ReadJsonDatas() = 0;
};
