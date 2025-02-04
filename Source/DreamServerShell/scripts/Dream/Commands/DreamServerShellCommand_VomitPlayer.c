class TDreamServerShellCommand_VomitPlayer: TDreamServerShellCommand
{
	void TDreamServerShellCommand_VomitPlayer()
	{
		Name = "VomitPlayer";
		Description = "Make the player vomit";
		MinimalParamCount = 1;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: VomitPlayer [PlayerID] <Duration>");
		result.Insert("Parameters:");
		result.Insert("  PlayerID - ID player from PlayerList");
		result.Insert("  Duration - Vomit duration (default 5 sec)");
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
			//Длительность рвоты
			int duration = data.Command.GetIntParamByIndex(1, 5);
			
			//Менеджер симптомов
			SymptomManager mgr = player.GetSymptomManager();
			
			//Рвота
			SymptomBase vomit = mgr.QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
			if (vomit)			
				vomit.SetDuration(duration);
		};
		
		return result;
	}
}