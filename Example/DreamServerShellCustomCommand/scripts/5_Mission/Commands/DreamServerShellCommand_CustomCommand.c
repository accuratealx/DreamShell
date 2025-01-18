class DreamServerShellCommand_Echo: TDreamServerShellCommand
{
	void DreamServerShellCommand_CustomCommand()
	{
		Name = "Echo";
		Description = "Description of echo command";
		MinimalParamCount = 0;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: echo <Text>");
		result.Insert("Parameters:");
		result.Insert("  Text - text");
		return result;
	}
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		//Ошибка во время выполнения, если не пусто, то на клиент отправится только эта строка
		result.Error = "";
		
		//Строка параметров от клиента
		result.Result.Insert("Input text: " + data.Command.ParamString());
		
		//Простой вывод
		result.Result.Insert("Result line1");
		result.Result.Insert("Result line2");
		
		return result;
	}
}