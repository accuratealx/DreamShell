class TDreamServerShellCommand_KillPlayer: TDreamServerShellCommand
{
	void TDreamServerShellCommand_KillPlayer()
	{
		Name = "KillPlayer";
		Description = "Kill player";
		MinimalParamCount = 1;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: KillPlayer [ID]");
		result.Insert("Parameters:");
		result.Insert("  ID - Player id");
		return result;
	}	
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		string id = data.Command.Parameters()[0];
		PlayerBase player = GetPlayerByID(id);
		if (!player)
			result.Error = string.Format("player id %1 not found", id);
		else {
			player.SetAllowDamage(true);
			player.SetHealth(0);
		};
		
		return result;
	}
}