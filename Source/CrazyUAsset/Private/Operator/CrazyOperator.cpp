#include "Operator/CrazyOperator.h"

#include "EditorAssetLibrary.h"
#include "AssetManagerEditorModule.h"
#include "UObject\SavePackage.h"

void UCrazyAssetOperator::OpenEditorUI(const FAssetData& Asset)
{
	GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(Asset.GetObjectPathString());
}

int UCrazyAssetOperator::SaveAsset(UObject* ObjectToSave)
{
	if (ObjectToSave && ObjectToSave->MarkPackageDirty())
	{
		UPackage* AssetPackage = ObjectToSave->GetOutermost();

		if (AssetPackage)
		{
			FString PackageFilePath = FPackageName::LongPackageNameToFilename(AssetPackage->GetName(), FPackageName::GetAssetPackageExtension());

			FSavePackageArgs SaveArgs;
			SaveArgs.TopLevelFlags = EObjectFlags::RF_Public | EObjectFlags::RF_Standalone;
			SaveArgs.Error = GError;
			SaveArgs.bForceByteSwapping = true;
			SaveArgs.SaveFlags = SAVE_None;

			return UPackage::SavePackage(AssetPackage, ObjectToSave, *PackageFilePath, SaveArgs) ? 1 : 0;
		}

		return 0;
	}

	return 0;
}

int FCrazyAssetOperator::SaveAsset(const FString& AssetToSave, bool bOnlyIfIsDirty)
{
	return UEditorAssetLibrary::SaveAsset(AssetToSave, bOnlyIfIsDirty) ? 1: 0;
}

void UCrazyAssetOperator::OpenSizeMapUI_SingleAsset(FAssetData & AssetIn)
{
	TArray<FAssetData> Assets;
	Assets.Add(AssetIn);

	return UCrazyAssetOperator::OpenSizeMapUI(Assets);
}

void FCrazyAssetOperator::OpenSizeMapUI(TSharedPtr<FAssetData> AssetIn)
{
	TArray<TSharedPtr<FAssetData>> Assets;
	Assets.Add(AssetIn);

	return FCrazyAssetOperator::OpenSizeMapUI(Assets);
}

void UCrazyAssetOperator::OpenSizeMapUI(TArray<FAssetData> AssetsIn)
{
	TArray<FAssetIdentifier> list;

	for (const FAssetData & AssetData : AssetsIn)
	{
		list.Add(FAssetIdentifier(AssetData.PackageName));
	}

	IAssetManagerEditorModule::Get().OpenSizeMapUI(list);
};

void FCrazyAssetOperator::OpenSizeMapUI(TArray<TSharedPtr<FAssetData>> AssetsIn)
{
	TArray<FAssetIdentifier> list;

	for (const TSharedPtr<FAssetData> & AssetData : AssetsIn)
	{
		list.Add(FAssetIdentifier(AssetData->PackageName));
	}

	IAssetManagerEditorModule::Get().OpenSizeMapUI(list);
};
