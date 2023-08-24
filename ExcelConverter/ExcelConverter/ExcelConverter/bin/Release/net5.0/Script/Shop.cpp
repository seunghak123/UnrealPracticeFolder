USTRUCT(BlueprintType)
struct FShopData
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditAnwhere, BlueprintReadOnly, Category= FurnitureData)
	int index;

	UPROPERTY(EditAnwhere, BlueprintReadOnly, Category= FurnitureData)
	int shop_id;

	UPROPERTY(EditAnwhere, BlueprintReadOnly, Category= FurnitureData)
	int shop_price;

	UPROPERTY(EditAnwhere, BlueprintReadOnly, Category= FurnitureData)
	string shop_id_string;

}