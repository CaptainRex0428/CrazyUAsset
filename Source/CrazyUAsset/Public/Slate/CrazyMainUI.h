#pragma once

#include "Log/CrazyLog.h"

#include "Widgets/SCompoundWidget.h"

class CRAZYUASSET_API SCrazyUAssetMainUI : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(SCrazyUAssetMainUI) {}
		SLATE_ARGUMENT(TArray<FString>, SelectedFolderPaths)
	SLATE_END_ARGS()

public:
	virtual void Construct(const FArguments& InArgs);

private:
	TArray<FString> FolderPaths;
	TSharedPtr<SWidget> AssetPickerWidget;
};