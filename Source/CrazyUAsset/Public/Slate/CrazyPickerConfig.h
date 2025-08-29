#pragma once

#include "Log/CrazyLog.h"

#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"

#include <type_traits>

/**
 * Creates an asset picker configuration with specified folder and package paths.
 *
 * This function generates a FAssetPickerConfig object that can be used to configure
 * asset selection dialogs or widgets in the Unreal Engine content browser.
 *
 * @param FolderPaths    Array of folder paths to include in the asset picker.
 * @param PackagePaths   Array of package paths to include in the asset picker.
 * @param AutoFixPath    If true, automatically fixes invalid path formats to ensure
 *                       they start with "/All". Default is true.
 *
 * @return FAssetPickerConfig    Configured asset picker ready for use.
 *
 * @note All paths in FolderPaths and PackagePaths arrays must start with "/All".
 *       If AutoFixPath is enabled, the function will attempt to correct invalid paths.
 *
 * Example usage:
 * @code
 * TArray<FName> Folders = {TEXT("/All/Content/Meshes"), TEXT("/All/Content/Textures")};
 * TArray<FName> Packages = {TEXT("/All/Game/Characters")};
 * FAssetPickerConfig Config = MakeAssetPickerConfig(Folders, Packages);
 * @endcode
 */
FAssetPickerConfig MakePickerConfig(TArray<FName> FolderPaths = {}, TArray<FName> PackgePaths = {}, bool bAutoFixPath = true);

FAssetPickerConfig MakePickerConfig(TArray<FString> FolderPaths = {}, TArray<FString> PackgePaths = {}, bool bAutoFixPath = true);

void AppendPickerConfigPaths(FAssetPickerConfig& Configuration, TArray<FName> FolderPaths = {}, TArray<FName> PackgePaths = {}, bool AutoFixPath = true);

template <typename T>
TSharedPtr<T> FindChildInWidgetByType(TSharedPtr<SWidget>& Widget, bool bEnableDebugLog = false)
{
	static_assert(std::is_base_of<SWidget, T>::value, "Template parameter T must be derived from SWidget");

	if (!Widget.IsValid())
	{
		return nullptr;
	}

	FString TargetTypeName = FString(ANSI_TO_TCHAR(typeid(T).name()));
	TargetTypeName.RemoveFromStart("class ");

	// 使用数组来存储待检查的Widget
	TArray<TSharedRef<SWidget>> WidgetsToCheck;
	WidgetsToCheck.Add(Widget.ToSharedRef());

	for (int32 Index = 0; Index < WidgetsToCheck.Num(); ++Index)
	{
		TSharedRef<SWidget> CurrentWidget = WidgetsToCheck[Index];
		FString WidgetTypeName = CurrentWidget->GetTypeAsString();

		if (bEnableDebugLog)
		{
			CrazyLogOnly("Checking widget: " + WidgetTypeName);
		}

		if (WidgetTypeName.Contains(TargetTypeName))
		{
			if (bEnableDebugLog)
			{
				CrazyLogOnly("FindChildInWidgetByType: Found target widget!");
			}
			return StaticCastSharedRef<T>(CurrentWidget);
		}

		// 将子Widget添加到检查列表
		FChildren* Children = CurrentWidget->GetChildren();
		if (Children)
		{
			for (int32 i = 0; i < Children->Num(); ++i)
			{
				WidgetsToCheck.Add(Children->GetChildAt(i));
			}
		}
	}

	if (bEnableDebugLog)
	{
		CrazyLogOnly("FindChildInWidgetByType: Could not find widget of type: " + TargetTypeName);
	}

	return nullptr;
}

// void SetAssetPickerConfig(FAssetPickerConfig& Configuration);