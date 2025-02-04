class TDreamServerShellCommand_KickPlayer: TDreamServerShellCommand
{
	void TDreamServerShellCommand_KickPlayer()
	{
		Name = "KickPlayer";
		Description = "Kick player";
		MinimalParamCount = 1;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: KickPlayer [PlayerID]");
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
			MissionServer mission = MissionServer.Cast(GetGame().GetMission());
			GetGame().SendLogoutTime(player, 0);
			mission.PlayerDisconnected(player, player.GetIdentity(), player.GetIdentity().GetId());
		};
		
		return result;
	}
}