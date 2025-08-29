#include "Checker/CrazyChecker.h"

#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"

#include "EditorAssetLibrary.h"

TArray<FString> FCrazyAssetChecker::GetCurrentContentBrowserSelectedPaths(bool bRemoveStartTag)
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
	IContentBrowserSingleton& ContentBrowser = ContentBrowserModule.Get();

	TArray<FString> SelectedPaths;
	ContentBrowser.GetSelectedFolders(SelectedPaths);

	if(bRemoveStartTag)
	{
		for (FString& path : SelectedPaths)
		{
			path.RemoveFromStart(L"/All");
		}
	}
	
	return SelectedPaths;
}

FString FCrazyAssetChecker::GetCurrentContentBrowserPath(bool bRemoveStartTag)
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
	IContentBrowserSingleton& ContentBrowser = ContentBrowserModule.Get();

	FContentBrowserItemPath Path = ContentBrowser.GetCurrentPath();
	FString PathStr = Path.GetVirtualPathString();

	if (bRemoveStartTag)
		PathStr.RemoveFromStart(L"/All");

	return PathStr;
}

TArray<FString> FCrazyAssetChecker::GetAssetReferencedPath(const FString& AssetPath, bool bLoadToCheck)
{
	return UEditorAssetLibrary::FindPackageReferencersForAsset(AssetPath, bLoadToCheck);
}

TArray<FString> FCrazyAssetChecker::GetAssetReferencedPath(const TSharedPtr<FAssetData>& AssetData)
{
	return GetAssetReferencedPath(AssetData->GetObjectPathString());
}

TArray<FString> UCrazyAssetChecker::GetAssetReferencedPath(const FAssetData& AssetData)
{
	return FCrazyAssetChecker::GetAssetReferencedPath(AssetData.GetObjectPathString());
}
