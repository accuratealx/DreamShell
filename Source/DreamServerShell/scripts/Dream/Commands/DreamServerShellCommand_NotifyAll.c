class TDreamServerShellCommand_NotifyAll: TDreamServerShellCommand
{
	void TDreamServerShellCommand_NotifyAll()
	{
		Name = "NotifyAll";
		Description = "Notify all users";
		MinimalParamCount = 1;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: NotifyAll [Message]");
		result.Insert("Parameters:");
		result.Insert("  Message - Just mesage");
		return result;
	}
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		string msg = data.Command.ParamString();
		SendNotify(msg, MESSAGE_DURATION, ICON_MESSAGE);
		
		return result;
	}
}