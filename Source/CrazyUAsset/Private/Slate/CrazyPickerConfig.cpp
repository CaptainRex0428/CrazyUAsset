#include "Slate/CrazyPickerConfig.h"

#include "Log/CrazyLog.h"
#include "Operator/CrazyOperator.h"
#include "Checker/CrazyChecker.h"

FAssetPickerConfig CreatePickerConfig(TArray<FName> FolderPaths, TArray<FName> PackgePaths, bool bAutoFixPath)
{
	// 配置AssetPicker
	FAssetPickerConfig AssetPickerConfig;
	AssetPickerConfig.InitialAssetViewType = EAssetViewType::List;
	AssetPickerConfig.InitialThumbnailSize = EThumbnailSize::Large;
	AssetPickerConfig.AssetShowWarningText = FText::FromString(L"No results !!!");
	AssetPickerConfig.bAddFilterUI = true;
	AssetPickerConfig.bAllowDragging = true;
	AssetPickerConfig.bAllowRename = true;

	AssetPickerConfig.bAllowNullSelection = false;	

	AssetPickerConfig.bCanShowClasses = true;
	AssetPickerConfig.bCanShowDevelopersFolder = true;

	AssetPickerConfig.bCanShowFolders = false;

	AssetPickerConfig.bCanShowRealTimeThumbnails = true;
	AssetPickerConfig.bFocusSearchBoxWhenOpened = true;

	AssetPickerConfig.bShowBottomToolbar = true;
	AssetPickerConfig.bShowPathInColumnView = true;
	AssetPickerConfig.bShowTypeInColumnView = true;
	AssetPickerConfig.bSortByPathInColumnView = true;

	AssetPickerConfig.OnAssetDoubleClicked = FOnAssetDoubleClicked::CreateStatic(&UCrazyAssetOperator::OpenEditorUI);

	// Referenced Column

	AssetPickerConfig.CustomColumns.Add(FAssetViewCustomColumn(
		FName(L"Referenced"),
		FText::FromString(L"Referenced Count"),
		FText::FromString("How many times referenced by other assets."),
		UObject::FAssetRegistryTag::TT_Numerical,
		FOnGetCustomAssetColumnData::CreateLambda(
			[](const FAssetData& AssetData, const FName& ColumnName) -> FString
			{
				TArray<FString> ReferencedPath = UCrazyAssetChecker::GetAssetReferencedPath(AssetData);
				return FString::FromInt(ReferencedPath.Num());
			})));




	if (bAutoFixPath) 
	{
		for (FName& path : FolderPaths)
		{
			if (!path.ToString().StartsWith("/All"))
			{
				FString fixPath = "/All" + path.ToString();
				path = FName(*fixPath);
			}
		}

		for (FName& name : PackgePaths)
		{
			if (!name.ToString().StartsWith("/All"))
			{
				FString fixName = "/All" + name.ToString();
				name = FName(*fixName);
			}
		}
	}

	AssetPickerConfig.Filter.PackagePaths.Empty();
	AssetPickerConfig.Filter.PackageNames.Empty();
	AssetPickerConfig.Filter.bRecursivePaths = true;

	AssetPickerConfig.Filter.PackagePaths.Append(FolderPaths);
	AssetPickerConfig.Filter.PackageNames.Append(PackgePaths);

	return AssetPickerConfig;
}

FAssetPickerConfig CreatePickerConfig(TArray<FString> FolderPaths, TArray<FString> PackgePaths, bool bAutoFixPath)
{
	TArray<FName> folderPaths_FName;
	TArray<FName> packageNames_FName;

	for(const FString& path: FolderPaths)
	{
		folderPaths_FName.Add(*path);
	}

	for (const FString& name : PackgePaths)
	{
		packageNames_FName.Add(*name);
	}

	return CreatePickerConfig(folderPaths_FName, packageNames_FName, bAutoFixPath);
}

void AppendPickerConfigPaths(FAssetPickerConfig& Configuration, TArray<FName> FolderPaths, TArray<FName> PackgePaths, bool AutoFixPath)
{

}
