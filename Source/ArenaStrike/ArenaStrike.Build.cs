// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ArenaStrike : ModuleRules
{
	public ArenaStrike(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
			{ "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities", "GameplayTasks" });

		PrivateDependencyModuleNames.AddRange(new string[] { "AnimGraphRuntime" });
	}
}