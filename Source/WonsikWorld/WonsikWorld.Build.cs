// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
public class WonsikWorld : ModuleRules
{
	public WonsikWorld(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "MyNetworkLibrary"});
		PrivateDependencyModuleNames.AddRange(new string[] { "MyNetworkLibrary" });
	}
}
