// Copyright Epic Games, Inc. All Rights Reserved.

#include "CrazyUAssetCommands.h"

#define LOCTEXT_NAMESPACE "FCrazyUAssetModule"

void FCrazyUAssetCommands::RegisterCommands()
{
	UI_COMMAND(Command_CrazyMainUI_Current, "CrazyUAsset", "Crazy Main UI", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(Command_CrazyMainUI_Selected, "CrazyUAsset", "Crazy Main UI", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
