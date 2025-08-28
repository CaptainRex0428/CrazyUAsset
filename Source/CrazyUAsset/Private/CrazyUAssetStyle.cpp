// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrazyUAssetStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FCrazyUAssetStyle::StyleInstance = nullptr;

void FCrazyUAssetStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FCrazyUAssetStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FCrazyUAssetStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("CrazyUAssetStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon32x32(32.0f, 32.0f);
const FVector2D Icon64x64(64.0f, 64.0f);

TSharedRef< FSlateStyleSet > FCrazyUAssetStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("CrazyUAssetStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("CrazyUAsset")->GetBaseDir() / TEXT("Resources"));

	Style->Set("CrazyUAsset.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	Style->Set("CrazyUAsset.MainUI", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FCrazyUAssetStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FCrazyUAssetStyle::Get()
{
	return *StyleInstance;
}
