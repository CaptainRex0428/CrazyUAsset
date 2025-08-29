#pragma once

#include "Log/CrazyLog.h"

#include "Widgets/SCompoundWidget.h"

#include "SAssetView.h"

class CRAZYUASSET_API SCrazyUAssetMainUI : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SCrazyUAssetMainUI) {}
		SLATE_ARGUMENT(TArray<FString>, SelectedFolderPaths)
	SLATE_END_ARGS()

public:
	virtual void Construct(const FArguments& InArgs);

	virtual void Update();

	void OnAnyAssetSelected(const FAssetData& AssetData);

private:
	TArray<FString> ScanningFolderPaths;

	TSharedPtr<SWidget> AssetPickerWidget;
	TSharedPtr<SAssetView> AssetViewWidget;

	TArray<FAssetData> SelectedAssets;
};