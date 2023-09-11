#pragma once
#include "UBaseData.h"
#include "UShopData.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Player, Log, All);



#define LOG(Category, Verbosity, String)    UE_LOG(Category, Verbosity, \
                                            TEXT("%s"), *FString::Printf(TEXT("%s : {%d} : %s"), \
                                            *FString(__FUNCTION__), __LINE__, String));
USTRUCT(BlueprintType)
struct FIRSTPROJECT_API FUShopData : public FUBaseData
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= FurnitureData)
	int index;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= FurnitureData)
	int shop_id;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= FurnitureData)
	int shop_price;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= FurnitureData)
	FString shop_id_string;
public: 
	//UShopData UserDataReadJson();
	static TArray<FUShopData> UserDataReadJsons();
};