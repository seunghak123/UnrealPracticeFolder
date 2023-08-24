USTRUCT(BlueprintType)
struct FUnitData
{
	GENERATED_BODY()
public: 
	UPROPERTY(EditAnwhere, BlueprintReadOnly, Category= FurnitureData)
	int index;

	UPROPERTY(EditAnwhere, BlueprintReadOnly, Category= FurnitureData)
	string unitName;

	UPROPERTY(EditAnwhere, BlueprintReadOnly, Category= FurnitureData)
	int unitHp;

}