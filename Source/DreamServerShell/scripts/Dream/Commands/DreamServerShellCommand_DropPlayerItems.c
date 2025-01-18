class TDreamServerShellCommand_DropPlayerItems: TDreamServerShellCommand
{
	void TDreamServerShellCommand_DropPlayerItems()
	{
		Name = "DropPlayerItems";
		Description = "Drop player items to the ground";
		MinimalParamCount = 1;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: DropPlayerItems [ID]");
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
			player.DropAllItems();
		};
		
		return result;
	}
}