#include "UShopData.h"

DEFINE_LOG_CATEGORY(Player);
//UShopData UShopData::UserDataReadJson()
//{
//	//TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField(TEXT("UShopData"));
//	UShopData* returnValue = &UShopData();
//	//returnValue.index = ReadJsonValue(JsonObject, TEXT("index"),int);
//	//returnValue.shop_id = ReadJsonValue(JsonObject, TEXT("shop_id"),int);
//	//returnValue.shop_price = ReadJsonValue(JsonObject, TEXT("shop_price"),int);
//	//returnValue.shop_id_string = ReadJsonValue(JsonObject, TEXT("shop_id_string"),FString());
//
//
//    return returnValue;
//}

TArray<FUShopData> FUShopData::UserDataReadJsons()
{
    TArray<FUShopData> ShopDataArray;
    // JSON 파일을 읽어들일 문자열 변수
    FString JsonString;
    FString FilePath = TEXT("C:\\Users\\AssortRock\\Desktop\\Json\\jshop.json");// =FPaths::EngineContentDir()+"Bundle\Json"+ "\JShop.json";  // JSON 파일 경로
    // JSON 파일 읽기
    if (FFileHelper::LoadFileToString(JsonString, *FilePath))
    {
        //LOG(Player, Log, TEXT("%s" ),JsonString);
        LOG(Player, Log, TEXT("Json!!"));
        TSharedPtr<FJsonValue> userJsonValue = TSharedPtr<FJsonValue>();
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
        if (FJsonSerializer::Deserialize(JsonReader, userJsonValue))
        {
            LOG(Player, Log, TEXT("Loading!!"));
            TArray<TSharedPtr<FJsonValue>> getJsonArray;
            getJsonArray = userJsonValue->AsArray();
            
            for (const TSharedPtr<FJsonValue>& ArrayItem : getJsonArray)
            {
                TSharedPtr<FJsonObject> JsonObject = ArrayItem->AsObject();
                if (JsonObject.IsValid())
                {
                    FUShopData ShopData ;
                    ShopData.index = JsonObject->GetIntegerField("index");
                    ShopData.shop_id = JsonObject->GetIntegerField("shop_id");
                    ShopData.shop_price = JsonObject->GetIntegerField("shop_price");
                    ShopData.shop_id_string = JsonObject->GetStringField("shop_id_string");
                    ShopDataArray.Add(ShopData);
                }
            }
            
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("JSON 파싱 실패"));
        }
    }

    // UShopData 객체 배열 반환
    return ShopDataArray;
}
