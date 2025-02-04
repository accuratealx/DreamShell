class TDreamServerShellCommand_BreakPlayerLeg: TDreamServerShellCommand
{
	void TDreamServerShellCommand_BreakPlayerLeg()
	{
		Name = "BreakPlayerLeg";
		Description = "Break player leg";
		MinimalParamCount = 1;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: BreakPlayerLeg [PlayerID]");
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
			ModifiersManager mgr = player.GetModifiersManager();
			if (mgr.IsModifierActive(eModifiers.MDF_BROKEN_LEGS))
				mgr.DeactivateModifier(eModifiers.MDF_BROKEN_LEGS);
			mgr.ActivateModifier(eModifiers.MDF_BROKEN_LEGS);
		};
		
		return result;
	}
}