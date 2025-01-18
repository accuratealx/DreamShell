class TDreamServerShellCommand_PlayerList: TDreamServerShellCommand
{
	void TDreamServerShellCommand_PlayerList()
	{
		Name = "PlayerList";
		Description = "Show player list";
		MinimalParamCount = 0;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: PlayerList <Full>");
		result.Insert("Parameters:");
		result.Insert("  Full - Show full information");
		return result;
	}	
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		result.Result.Insert("PlayerList:");		
		
		//Определить режим
		bool full = false;
		if (data.Command.Parameters().Count() > 0)
			if (DreamShell_StrToLower(data.Command.Parameters()[0]) == "full")
				full = true;
		
		array<Man> players = new array<Man>();
		GetGame().GetPlayers(players);
		int count = 0;
		foreach (auto p: players)
		{
			PlayerIdentity identity = p.GetIdentity();
			if (!identity)
				continue;
			
			string pName = identity.GetName();
			string pSteamID = identity.GetPlainId();
			string pOrder = DreamShell_IntToStringWithSpaces(identity.GetPlayerId(), 2);
		
			string s = "";
			if (full)
				//order SteamID pBattleyeyID Name
				s = string.Format("%1 %2 %3 %4", pOrder, pSteamID, identity.GetId(), pName);
			else
				//order SteamID Name
				s = string.Format("%1 %2 %3", pOrder, pSteamID, pName);
			
			result.Result.Insert("  " + s);
			count++;
		}
		
		result.Result.Insert("Count: " + count.ToString());
		return result;
	}
}