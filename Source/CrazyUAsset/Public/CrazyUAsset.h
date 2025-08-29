// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FCrazyUAssetModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void OnCrazyMainUIClicked_CurrentBrowser();
	void OnCrazyMainUIClicked_Selected();
	
private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnCrazyMainUISpawn(const class FSpawnTabArgs& SpawnTabArgs);

private:

	TSharedPtr<class FUICommandList> CrazyUAssetCommandList;

#pragma region MainUI Info
	
	TArray<FString> CrazyMainUISelectedFolderPaths;
	TArray<FString> CrazyMainUISelectedPackageNames;

	TSharedPtr<class SDockTab> CrazyMainUIDockerTab;
	TSharedPtr<class SCrazyUAssetMainUI> CrazyMainUI;

#pragma endregion
	
};
