class CfgPatches
{
	class DreamShellCustomBG
	{
		requiredAddons[] = {
			"DreamShell"
		};
	};
};

class CfgMods
{
	class DreamShellCustomBG
	{
		type = "mod";
		dependencies[] = {
			"World"
		};
		
		class defs
		{
			class worldScriptModule
			{
				files[] = {
					"DreamShellCustomBG/scripts/4_world"
				};
			};
		};
	};
};
