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
		result.Insert("Example: KickPlayer [ID]");
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
			MissionServer mission = MissionServer.Cast(GetGame().GetMission());
			GetGame().SendLogoutTime(player, 0);
			mission.PlayerDisconnected(player, player.GetIdentity(), player.GetIdentity().GetId());
		};
		
		return result;
	}
}