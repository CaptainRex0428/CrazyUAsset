// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrazyUAsset.h"
#include "CrazyUAssetStyle.h"
#include "CrazyUAssetCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"

static const FName CrazyUAssetMainUIName("CrazyUAsset");

#define LOCTEXT_NAMESPACE "FCrazyUAssetModule"

void FCrazyUAssetModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCrazyUAssetStyle::Initialize();
	FCrazyUAssetStyle::ReloadTextures();

	FCrazyUAssetCommands::Register();
	
#pragma region Map Commands (How)

	CrazyUAssetCommandList = MakeShareable(new FUICommandList);

	CrazyUAssetCommandList->MapAction(
		FCrazyUAssetCommands::Get().CrazyMainUI_Command,
		FExecuteAction::CreateRaw(this, &FCrazyUAssetModule::CrazyMainUIClicked),
		FCanExecuteAction());

#pragma endregion

#pragma region Register Menus (Where)

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCrazyUAssetModule::RegisterMenus));

#pragma endregion

#pragma region Register Tabs (What)

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(CrazyUAssetMainUIName, 
		FOnSpawnTab::CreateRaw(this, &FCrazyUAssetModule::OnSpawnCrazyMainUI))
		.SetDisplayName(LOCTEXT("FCrazyUAssetTabTitle", "CrazyUAsset"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

#pragma endregion

}

void FCrazyUAssetModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FCrazyUAssetStyle::Shutdown();

	FCrazyUAssetCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CrazyUAssetMainUIName);
}

TSharedRef<SDockTab> FCrazyUAssetModule::OnSpawnCrazyMainUI(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FCrazyUAssetModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("CrazyUAsset.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
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
}

void FCrazyUAssetModule::CrazyMainUIClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(CrazyUAssetMainUIName);
}

void FCrazyUAssetModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

	{
		ContentBrowserModule.GetAllPathViewContextMenuExtenders().Add(
			FContentBrowserMenuExtender_SelectedPaths::CreateLambda([this](const TArray<FString>& SelectedPaths)
				{
					TSharedRef<FExtender> MenuExtender(new FExtender());

					SelectedContentFolderPaths = SelectedPaths;

					if (SelectedPaths.Num() > 0)
					{
						MenuExtender->AddMenuExtension(
							FName("PathViewFolderOptions"),
							EExtensionHook::After,
							CrazyUAssetCommandList,
							FMenuExtensionDelegate::CreateLambda([this](FMenuBuilder& MenuBuilder)
								{
									MenuBuilder.AddMenuEntry(
										FCrazyUAssetCommands::Get().CrazyMainUI_Command,
										CrazyUAssetMainUIName,
										LOCTEXT("CrazyMainUI_Label", "CrazyMainUI"),
										TAttribute<FText>(),
										FSlateIcon(FCrazyUAssetStyle::GetStyleSetName(), "CrazyUAsset.MainUI"));
								}));
					}

					return MenuExtender;
				}));
	}

	{
		UToolMenu* ContentBrowserToolBar = UToolMenus::Get()->ExtendMenu("ContentBrowser.ToolBar");
		{
			FToolMenuSection& Section = ContentBrowserToolBar->AddSection(
				CrazyUAssetMainUIName,
				LOCTEXT("CrazyMainUI_Label", "CrazyMainUI"),
				FToolMenuInsert(FName("Save"), EToolMenuInsertType::After)
			);

			FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FCrazyUAssetCommands::Get().CrazyMainUI_Command));
			Entry.SetCommandList(CrazyUAssetCommandList);
			Entry.Icon = FSlateIcon(FCrazyUAssetStyle::GetStyleSetName(), "CrazyUAsset.MainUI");
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCrazyUAssetModule, CrazyUAsset)