class TDreamServerShellCommand_Shutdown: TDreamServerShellCommand
{
	void TDreamServerShellCommand_Shutdown()
	{
		Name = "Shutdown";
		Description = "Turn off the server";
		MinimalParamCount = 0;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: Shutdown <DelaySec>");
		result.Insert("Parameters:");
		result.Insert("  DelaySec - delay before shutdown (default 90 sec)");
		return result;
	}	
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		//Определить длительность
		int delay = data.Command.GetIntParamByIndex(0, 90);
		
		//Послать сообщение
		SendNotify(string.Format("server will shut down for update in %1 seconds", delay));
				
		if (delay > 10)
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ShutdownLastMessage, (delay - 10) * 1000, false);
		else
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(Shutdown, delay * 1000, false);
		
		return result;
	}
	
	private void ShutdownLastMessage()
	{
		//Отослать последнее предупреждение
		SendNotify(string.Format("server will shut down for update in %1 seconds", 10));
		
		//Выполнить выключение через 10 секунд
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(Shutdown, 10 * 1000, false);
	}
	
	private void Shutdown()
	{
		GetGame().RequestExit(0);
	}
}