// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CrazyUAsset : ModuleRules
{
	public CrazyUAsset(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				System.IO.Path.GetFullPath(Target.RelativeEnginePath) + "/Source/Developer/SkeletalMeshUtilitiesCommon/Public",
			}
			);


		PrivateIncludePaths.AddRange(
			new string[] {
				System.IO.Path.GetFullPath(Target.RelativeEnginePath) + "/Source/Editor/Blutility/Private",
				System.IO.Path.GetFullPath(Target.RelativeEnginePath) + "/Source/Editor/UnrealEd/Private",
				System.IO.Path.GetFullPath(Target.RelativeEnginePath) + "/Source/Runtime/AssetRegistry/Private",
				System.IO.Path.GetFullPath(Target.RelativeEnginePath) + "/Source/Developer/AssetTools/Private",
				System.IO.Path.GetFullPath(Target.RelativeEnginePath) + "/Source/Runtime/Slate/Private",
			}
			);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",

				"Blutility",
				"EditorScriptingUtilities",
				"EditorSubsystem",
				"EditorFramework",	

				"UMG",
				"UMGEditor",

				"Niagara",
				"NiagaraCore",
				
				"AssetRegistry",
				"AssetTools",

				"ContentBrowser",
				"ContentBrowserData",

				"SkeletalMeshUtilitiesCommon",
				
				"AssetManagerEditor",

				"HairStrandsCore",

				"LevelEditor",

				"TextureEditor",
				"TextureUtilitiesCommon",

				"PhysicsCore",

				"InterchangeCore",
				"InterchangeEngine",
				"InterchangePipelines",
				"InterchangeNodes",

				
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"Engine",
				"Slate",
				"SlateCore",
				"UnrealEd",
				"ToolMenus",
				"CoreUObject",
				
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
