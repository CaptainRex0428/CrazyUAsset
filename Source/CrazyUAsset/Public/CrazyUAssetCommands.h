// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Framework/Commands/Commands.h"
#include "CrazyUAssetStyle.h"

class FCrazyUAssetCommands : public TCommands<FCrazyUAssetCommands>
{
public:

	FCrazyUAssetCommands()
		: TCommands<FCrazyUAssetCommands>(TEXT("CrazyUAsset"), NSLOCTEXT("Contexts", "CrazyUAsset", "CrazyUAsset Plugin"), NAME_None, FCrazyUAssetStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > Command_CrazyMainUI_Current;
	TSharedPtr< FUICommandInfo > Command_CrazyMainUI_Selected;
};