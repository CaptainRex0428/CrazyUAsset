// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrazyUAssetCommands.h"

#define LOCTEXT_NAMESPACE "FCrazyUAssetModule"

void FCrazyUAssetCommands::RegisterCommands()
{
	UI_COMMAND(CrazyMainUI_Command, "CrazyUAsset", "Crazy Main UI.", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
