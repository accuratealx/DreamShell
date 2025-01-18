class TDreamServerShellCommand_Version: TDreamServerShellCommand
{
	void TDreamServerShellCommand_Version()
	{
		Name = "Version";
		Description = "Show system version";
		MinimalParamCount = 0;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: Version");
		return result;
	}	
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		result.Result.Insert("Version " + data.Version);
		return result;
	}
}