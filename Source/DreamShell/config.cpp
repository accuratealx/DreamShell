class CfgPatches
{
	class DreamShell
	{
		requiredAddons[] = {};
	};
};

class CfgMods
{
	class DreamShell
	{
		type = "mod";
		dependencies[] = {
			"World",
			"Mission"
		};
		
		inputs="DreamShell/DreamShell/inputs.xml";
		
		class defs
		{
			class worldScriptModule
			{
				files[] = {
					"DreamShell/DreamShell/scripts/4_world",
					"DreamShell/DreamShell/scripts/Dream"
				};
			};
			class missionScriptModule
			{
				files[] = {
					"DreamShell/DreamShell/scripts/5_mission"
				};
			};
		};
	};
};
