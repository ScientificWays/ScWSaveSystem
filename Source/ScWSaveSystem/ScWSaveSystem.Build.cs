// Scientific Ways

using UnrealBuildTool;
using System.IO; // for Path

public class ScWSaveSystem : ModuleRules
{
	public ScWSaveSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[]
		{

		});

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",

			"ScWGameCore",
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			
		});
	}
}
