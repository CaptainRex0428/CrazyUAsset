// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CrazyUAsset : ModuleRules
{
	public CrazyUAsset(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		CppCompileWarningSettings.UnsafeTypeCastWarningLevel = WarningLevel.Error;

		PublicIncludePaths.AddRange(
			new string[] {
				System.IO.Path.GetFullPath(Target.RelativeEnginePath) + "/Source/Developer/SkeletalMeshUtilitiesCommon/Public",
			}
			);

		PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"MainFrame",
				"StatsViewer",
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

		PublicIncludePathModuleNames.AddRange(
			new string[] {
				"AssetTools",
				"CollectionManager",
				"ContentBrowserData",
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",

				"Blutility",
				"EditorScriptingUtilities",
				"EditorSubsystem",
				"EditorStyle",
				"EditorFramework",
				"EditorWidgets",

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

				"TargetPlatform",

				
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"ApplicationCore",
				"Engine",
				"Slate",
				"SlateCore",
				"UnrealEd",
				"ToolMenus",
				"CoreUObject",
				"Json",
				"CollectionManager",

				"ContentBrowser",
				"ContentBrowserData",

				"WorkspaceMenuStructure",
				"AssetDefinition",
				"AppFramework",
				"Core",
				"CoreUObject",
				"Documentation",
				"DeveloperSettings",
				"ApplicationCore",
				"InputCore",
				"EditorConfig",
				"EditorStyle",
				"AssetTools",
				"ContentBrowserData",
				"SourceControl",
				"SourceControlWindows",
				"WorkspaceMenuStructure",
				"EditorFramework",
				"EditorWidgets",
				"AddContentDialog",
				"AssetRegistry",
				"AssetTagsEditor",
				"StatusBar",
				"ToolWidgets",
				"TelemetryUtils",
				"TypedElementFramework",
				"PropertyEditor",
				"KismetCompiler",
				"EditorWidgets",
				"TreeMap",
				"ToolMenus",
				"ToolWidgets",
				
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
