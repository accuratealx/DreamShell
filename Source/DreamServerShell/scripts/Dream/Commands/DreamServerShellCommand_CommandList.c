class TDreamServerShellCommand_CommandList: TDreamServerShellCommand
{
	void TDreamServerShellCommand_CommandList()
	{
		Name = "CommandList";
		Description = "Show list of all commands";
		MinimalParamCount = 0;
	}

	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: CommandList");
		return result;
	}	
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		//Отсортируем список команд
		array<string> list = new array<string>();
		for (int j = 0; j < data.CommandList.Count(); j++)
		{
			auto cmd = data.CommandList.Get(j);
			list.Insert("  " + cmd.Name + " - " + cmd.Description);
		}
		list.Sort();
		
		//Выведем результат
		result.Result.Insert("Command list:");
		for (int i = 0; i < list.Count(); i++)
			result.Result.Insert(list.Get(i));
		result.Result.Insert("Count: " + data.CommandList.Count());
		
		return result;
	}
}