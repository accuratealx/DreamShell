class CfgPatches
{
	class DreamServerShellCustomCommand
	{
		requiredAddons[] = {
			"DreamServerShell"
		};
	};
};

class CfgMods
{
	class DreamServerShellCustomCommand
	{
		type = "mod";
		dependencies[] = {
			"Mission"
		};

		class defs
		{
			class missionScriptModule
			{
				files[] = {
					"DreamServer/DreamServerShellCustomCommand/scripts/5_mission"
				};				
			};
		};
	};
};
