// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LearnUnreal5CPP : ModuleRules
{
	public LearnUnreal5CPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
