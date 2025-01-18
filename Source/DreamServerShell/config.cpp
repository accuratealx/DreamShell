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
					"DreamServer/DreamServerShell/scripts/4_world"
				};
			};
			class missionScriptModule
			{
				files[] = {
					"DreamServer/DreamServerShell/scripts/5_mission",
					"DreamServer/DreamServerShell/scripts/Dream"
				};				
			};
		};
	};
};
