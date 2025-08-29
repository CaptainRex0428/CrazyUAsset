#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "AssetManagerEditorModule.h"

#include "CrazyChecker.generated.h"


class CRAZYUASSET_API FCrazyAssetChecker : public UAssetActionUtility
{
public:
#pragma region EditorChecker

	static TArray<FString> GetCurrentContentBrowserSelectedPaths(bool bRemoveStartTag = false);

	static FString GetCurrentContentBrowserPath(bool bRemoveStartTag = false);
	
	
#pragma endregion
	
	static TArray<FString> GetAssetReferencedPath(const FString& AssetPath, bool bLoadToCheck = false);
	
	static TArray<FString> GetAssetReferencedPath(const TSharedPtr<FAssetData>& AssetData);	
};

UCLASS()
class CRAZYUASSET_API UCrazyAssetChecker : public UAssetActionUtility
{
	GENERATED_BODY()

public:
#pragma region EditorChecker
	

#pragma endregion
	
	UFUNCTION(BlueprintCallable, Category = "CrazyAsset|Checker", meta = (CallInEditor = "true"))
	static TArray<FString> GetAssetReferencedPath(const FAssetData& AssetData);

};