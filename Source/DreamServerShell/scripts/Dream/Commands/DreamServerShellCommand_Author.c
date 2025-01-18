class TDreamServerShellCommand_Author: TDreamServerShellCommand
{
	void TDreamServerShellCommand_Author()
	{
		Name = "Author";
		Description = "Show author";
		MinimalParamCount = 0;
	}

	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: Autor");
		return result;
	}
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		//Человек, который придумал экранировать символы через \ полный валенок
		result.Result.Insert("    _                                  _            _     _       ");
		result.Result.Insert("   / \\    ___  ___  _   _  _ __  __ _ | |_  ___    / \\   | |__  __");
		result.Result.Insert("  / _ \\  / __|/ __|| | | || '__|/ _` || __|/ _ \\  / _ \\  | |\\ \\/ /");
		result.Result.Insert(" / ___ \\| (__| (__ | |_| || |  | (_| || |_|  __/ / ___ \\ | | >  < ");
		result.Result.Insert("/_/   \\_\\\\___|\\___| \\__,_||_|   \\__,_| \\__|\\___|/_/   \\_\\|_|/_/\\_\\");
		result.Result.Insert("   ____                            _  _                           ");
		result.Result.Insert("  / __ \\   __ _  _ __ ___    __ _ (_)| |    ___  ___   _ __ ___   ");
		result.Result.Insert(" / / _` | / _` || '_ ` _ \\  / _` || || |   / __|/ _ \\ | '_ ` _ \\  ");
		result.Result.Insert("| | (_| || (_| || | | | | || (_| || || | _| (__| (_) || | | | | | ");
		result.Result.Insert(" \\ \\__,_| \\__, ||_| |_| |_| \\__,_||_||_|(_)\\___|\\___/ |_| |_| |_| ");
		result.Result.Insert("  \\____/  |___/                                                   ");
		
		return result;
	}
}
