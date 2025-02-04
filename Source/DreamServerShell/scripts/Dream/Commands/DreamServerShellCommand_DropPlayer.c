class TDreamServerShellCommand_DropPlayer: TDreamServerShellCommand
{
	void TDreamServerShellCommand_DropPlayer()
	{
		Name = "DropPlayer";
		Description = "Knock a player unconscious";
		MinimalParamCount = 1;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: DropPlayer [PlayerID]");
		result.Insert("Parameters:");
		result.Insert("  PlayerID - ID player from PlayerList");
		return result;
	}	
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		string id = data.Command.GetStrParamByIndex(0);
		PlayerBase player = GetPlayerByID(id);
		if (!player)
			result.Error = string.Format(ERROR_PLAYER_NOT_FOUND_FMT, id);
		else {
			DayZPlayerSyncJunctures.SendPlayerUnconsciousness(player, true);
		};

		return result;
	}
}