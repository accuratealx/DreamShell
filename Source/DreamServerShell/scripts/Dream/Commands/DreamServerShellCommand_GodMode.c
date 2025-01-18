class TDreamServerShellCommand_GodMode: TDreamServerShellCommand
{
	void TDreamServerShellCommand_GodMode()
	{
		Name = "GodMode";
		Description = "Change / status of god mode";
		MinimalParamCount = 1;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: GodMode [ID] <Mode>");
		result.Insert("Parameters:");
		result.Insert("  ID - Player id");
		result.Insert("  Mode - On / Off (if empty show status)");
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
			string name = player.GetIdentity().GetName();
			bool mode;
			
			if (data.Command.Parameters().Count() >= 2)
			{
				mode = data.Command.GetBoolParamByIndex(1);
				player.SetAllowDamage(!mode);
			} else {
				mode = !player.GetAllowDamage();
			}
			result.Result.Insert(string.Format("GodMode %1 = %2", name, BoolToString(mode)));
		};
		
		return result;
	}
}