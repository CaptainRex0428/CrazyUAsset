#include "Checker/CrazyChecker.h"

#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"

TArray<FString> FCrazyChecker::GetCurrentContentBrowserSelectedPaths()
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
	IContentBrowserSingleton& ContentBrowser = ContentBrowserModule.Get();

	TArray<FString> SelectedPaths;
	ContentBrowser.GetSelectedFolders(SelectedPaths);

	for (FString& path : SelectedPaths)
	{
		path.RemoveFromStart(L"/All");
	}

	return SelectedPaths;
}

FString FCrazyChecker::GetCurrentContentBrowserPath()
{
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));
	IContentBrowserSingleton& ContentBrowser = ContentBrowserModule.Get();

	FContentBrowserItemPath Path = ContentBrowser.GetCurrentPath();
	FString PathStr = Path.GetVirtualPathString();
	PathStr.RemoveFromStart(L"/All");

	return PathStr;
}
