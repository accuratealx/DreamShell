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
		
		inputs="Dream/DreamShell/inputs.xml";
		
		class defs
		{
			class worldScriptModule
			{
				files[] = {
					"Dream/DreamShell/scripts/4_world",
					"Dream/DreamShell/scripts/Dream"
				};
			};
			class missionScriptModule
			{
				files[] = {
					"Dream/DreamShell/scripts/5_mission"
				};
			};
		};
	};
};
