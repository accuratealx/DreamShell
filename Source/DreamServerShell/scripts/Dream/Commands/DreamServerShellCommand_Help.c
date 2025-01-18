class TDreamServerShellCommand_Help: TDreamServerShellCommand
{
	void TDreamServerShellCommand_Help()
	{
		Name = "Help";
		Description = "Show help for command";
		MinimalParamCount = 0;
	}

	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: Help <CommandName>");
		result.Insert("Parameters:");
		result.Insert("  CommandName - command name");
		return result;
	}
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		if (data.Command.Parameters().Count() == 0)
			result.Result = Help();
		else {
			string cmdName = data.Command.Parameters().Get(0);
			TDreamServerShellCommand cmd = data.CommandList.GetCommand(cmdName);
			
			if (cmd == null)
				result.Error = string.Format("Command '%1' not found", cmdName);
			else
				result.Result = cmd.Help();
		}
		
		return result;
	}
}