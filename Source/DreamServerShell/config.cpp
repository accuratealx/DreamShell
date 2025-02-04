class CfgPatches
{
	class DreamServerShell
	{
		requiredAddons[] = {
			"DreamShell"
		};
	};
};

class CfgMods
{
	class DreamServerShell
	{
		type = "mod";
		dependencies[] = {
			"World",
			"Mission"
		};

		class defs
		{
			class worldScriptModule
			{
				files[] = {
					"DreamShell/DreamServerShell/scripts/4_world"
				};
			};
			class missionScriptModule
			{
				files[] = {
					"DreamShell/DreamServerShell/scripts/5_mission",
					"DreamShell/DreamServerShell/scripts/Dream"
				};				
			};
		};
	};
};
