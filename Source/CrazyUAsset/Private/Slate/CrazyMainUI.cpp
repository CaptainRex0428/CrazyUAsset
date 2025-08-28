#include "Slate/CrazyMainUI.h"

#include "LevelEditor.h"
#include "ToolMenus.h"

#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SWindow.h"

#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"

#include "AssetRegistry/AssetRegistryModule.h"

void SCrazyUAssetMainUI::Construct(const FArguments& InArgs)
{
	this->FolderPaths = InArgs._SelectedFolderPaths;

	FString paths;

	for (auto path : this->FolderPaths)
	{
		paths += path;
		paths += "\n";
	}

	FText WidgetText = FText::Format(
		FTextFormat(FText::FromString(TEXT("Add code to {0} in {1} to override this window's contents.\nSelected folders:\n{2}"))),
		FText::FromString(TEXT("FCrazyUAssetModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("CrazyUAsset.cpp")),
		FText::FromString(paths)
	);

	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	FARFilter DebugFilter;
	DebugFilter.PackagePaths.Add(FName("/All/Game/EasyTechArt_Unreal"));
	DebugFilter.bRecursivePaths = true;

	// 配置AssetPicker
	FAssetPickerConfig AssetPickerConfig;
	AssetPickerConfig.InitialAssetViewType = EAssetViewType::Column;
	AssetPickerConfig.AssetShowWarningText = FText::FromString(L"No results !!!");
	AssetPickerConfig.bAddFilterUI = true;
	AssetPickerConfig.bAllowDragging = true;
	AssetPickerConfig.bAllowNullSelection = true;
	AssetPickerConfig.bAllowRename = true;
	AssetPickerConfig.bCanShowClasses = true;
	AssetPickerConfig.bCanShowDevelopersFolder = true;
	AssetPickerConfig.bCanShowFolders = false;
	AssetPickerConfig.bCanShowRealTimeThumbnails = true;
	AssetPickerConfig.bFocusSearchBoxWhenOpened = true;
	AssetPickerConfig.bShowBottomToolbar = true;
	AssetPickerConfig.bShowPathInColumnView = true;
	AssetPickerConfig.bShowTypeInColumnView = true;
	AssetPickerConfig.bSortByPathInColumnView = true;
	AssetPickerConfig.InitialThumbnailSize = EThumbnailSize::Medium;
	AssetPickerConfig.Filter = DebugFilter;

#pragma region Construct Framework

	TSharedPtr<SVerticalBox> MainBox = SNew(SVerticalBox);

	// 创建AssetPicker widget
	this -> AssetPickerWidget = ContentBrowserModule.Get().CreateAssetPicker(AssetPickerConfig);

	MainBox->AddSlot()
		.AutoHeight()
		[
			// Put your tab content here!
			SNew(SBox)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
						.Text(WidgetText)
				]
		];

	MainBox->AddSlot()
		.FillHeight(1.f)
		[
			SNew(SBorder)
				.Padding(FMargin(3))
				.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
				[
					this->AssetPickerWidget.ToSharedRef()
				]
		];

#pragma endregion

	this->ChildSlot
		[
			MainBox.ToSharedRef()
		];

}