#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "AssetManagerEditorModule.h"


class CRAZYUASSET_API FCrazyChecker : public UAssetActionUtility
{
public:
#pragma region EditorChecker

	static TArray<FString> GetCurrentContentBrowserSelectedPaths(bool bRemoveStartTag = false);
	static FString GetCurrentContentBrowserPath();

#pragma endregion

};