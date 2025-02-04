class TDreamServerShellCommand_NotifyPlayer: TDreamServerShellCommand
{
	void TDreamServerShellCommand_NotifyPlayer()
	{
		Name = "NotifyPlayer";
		Description = "Notify player";
		MinimalParamCount = 1;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: NotifyPlayer [PlayerID] [Message]");
		result.Insert("Parameters:");
		result.Insert("  PlayerID - ID player from PlayerList");
		result.Insert("  Message - Just mesage");
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
			//Получить сырое сообщение без первого параметра
			string msg = data.Command.ParamStringFromIndex(1);
			SendNotifyToPlayer(player, msg, MESSAGE_DURATION, ICON_MESSAGE);
		};
		
		return result;
	}
}