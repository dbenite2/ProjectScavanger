// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Scavanger : ModuleRules
{
	public Scavanger(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
