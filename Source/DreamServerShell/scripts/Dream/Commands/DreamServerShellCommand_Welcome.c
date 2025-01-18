class TDreamServerShellCommand_Welcome: TDreamServerShellCommand
{
	void TDreamServerShellCommand_Welcome()
	{
		Name = "Welcome";
		Description = "Welcome text";
		MinimalParamCount = 0;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: Welcome");
		return result;
	}	
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		result.Result.Insert("                       ( O   O )                       ");
		result.Result.Insert("____________________oOO___(_)___OOo____________________");
		result.Result.Insert("");
		result.Result.Insert("Version - show version");
		result.Result.Insert("Welcome - show this text");
		result.Result.Insert("Help <CommandName> - show command help");
		result.Result.Insert("CommandList - list all commands");

		return result;
	}
}