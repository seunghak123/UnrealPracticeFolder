#include "OHGameResourceManager.h"
//#include <HttpModule.h>

// 기본값 설정
AOHGameResourceManager::AOHGameResourceManager()
{
	// 모든 프레임에서 Tick()을 호출하도록 이 actor을(를) 설정합니다. 필요하지 않은 경우 이 기능을 해제하여 성능을 향상시킬 수 있습니다.
	PrimaryActorTick.bCanEverTick = true;
}

// 게임이 시작되거나 생성될 때 호출됩니다.
void AOHGameResourceManager::BeginPlay()
{
	Super::BeginPlay();

	//Gamesource load

}

// 매 프레임마다 호출됨
void AOHGameResourceManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//void AOHGameResourceManager::StartupModule()

    // Register the HttpModule callback
    //FHttpModule::Get().SetHttpDownloadHandler(MakeShareable(new FMyHttpDownloadHandler));


//void AOHGameResourceManager::ShutdownModule()

    // Unregister the HttpModule callback
    //FHttpModule::Get().SetHttpDownloadHandler(nullptr);


//void AOHGameResourceManager::OnRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)

    //if (bWasSuccessful && Response.IsValid() && Response.GetContentLength() > 0)
    //{
    //    // Get the downloaded content
    //    TArray<uint8> Content;
    //    Content.Append((const uint8*)Response->GetContent().GetData(), Response->GetContentLength());

    //    // Save the content to a local .pak file
    //    FString PakFilePath = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("DownloadedPak.pak"));
    //    FFileHelper::SaveArrayToFile(Content, *PakFilePath);

    //    // Perform the patching process (e.g., replacing existing .pak)
    //    // ... Your patching logic here ...

    //    UE_LOG(LogTemp, Warning, TEXT("Downloaded .pak file saved to: %s"), *PakFilePath);
    //}
    //else
    //{
    //    UE_LOG(LogTemp, Error, TEXT("Download failed."));
    //}


//void AOHGameResourceManager::DownloadPakFile(const FString& Url)

    //TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    //Request->OnProcessRequestComplete().BindRaw(this, &FMyHttpDownloadHandler::OnRequestComplete);
    /*Request->SetURL(Url);
    Request->SetVerb(TEXT("GET"));
    Request->ProcessRequest();*/
