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

#include "Slate/CrazyPickerConfig.h"

void SCrazyUAssetMainUI::Construct(const FArguments& InArgs)
{
	this->ScanningFolderPaths = InArgs._SelectedFolderPaths;

	FString paths;

	for (auto path : this->ScanningFolderPaths)
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

	// 配置AssetPicker
	FAssetPickerConfig AssetPickerConfig = MakePickerConfig(this->ScanningFolderPaths);

	AssetPickerConfig.OnAssetSelected = FOnAssetSelected::CreateSP(this,&SCrazyUAssetMainUI::OnAnyAssetSelected);

#pragma region Construct Framework

	TSharedPtr<SVerticalBox> MainBox = SNew(SVerticalBox);

	// 创建AssetPicker widget
	this -> AssetPickerWidget = ContentBrowserModule.Get().CreateAssetPicker(AssetPickerConfig);
	this -> AssetViewWidget = FindChildInWidgetByType<SAssetView>(this->AssetPickerWidget);

	if (!this->AssetViewWidget.IsValid())
	{
		CrazyLogOnly("[Attention] SAssetView widget doesn't exist.", -1);
	}

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

void SCrazyUAssetMainUI::Update()
{

}

void SCrazyUAssetMainUI::OnAnyAssetSelected(const FAssetData& AssetData)
{
	this->SelectedAssets = this->AssetViewWidget->GetSelectedAssets();

	CrazyLogOnly(FString::Printf(L"Selected Assets Count:%d", this->SelectedAssets.Num()));

}
