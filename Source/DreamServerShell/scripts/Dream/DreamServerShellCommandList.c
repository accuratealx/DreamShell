typedef map<string, ref TDreamServerShellCommand> TDreamServerShellCommandAray;

class TDreamServerShellCommandList: Managed
{
	private ref TDreamServerShellCommandAray FCommandList = new TDreamServerShellCommandAray();
	
	void TDreamServerShellCommandList()
	{
		RegisterCommands();
	}
	
	//Вернуть команду
	TDreamServerShellCommand GetCommand(string cmdName)
	{
		TDreamServerShellCommand cmd;
		FCommandList.Find(DreamShell_StrToLower(cmdName), cmd);
		return cmd;
	}
	
	void DumpToLog()
	{
		Print("");
		DreamShell_Log("TDreamServerShellCommandList:");
		DreamShell_Log("  Count = " + FCommandList.Count().ToString());
		DreamShell_Log("  Items:");
		for (int i = 0; i < FCommandList.Count(); i++)
		{
			TDreamServerShellCommand cmd = FCommandList.Get(FCommandList.GetKey(i));
			DreamShell_Log("    " + cmd.Name);
		}
	}
	
	int Count()
	{
		return FCommandList.Count();
	}
	
	TDreamServerShellCommand Get(int index)
	{
		return FCommandList.GetElement(index);
	}

	private void AddCommand(TDreamServerShellCommand command)
	{
		string name = command.Name;
		FCommandList.Insert(DreamShell_StrToLower(name), command);
	}	
		
	void RegisterCommands()
	{
		AddCommand(new TDreamServerShellCommand_Author());
		AddCommand(new TDreamServerShellCommand_BreakPlayerLeg());
		AddCommand(new TDreamServerShellCommand_CommandList());
		AddCommand(new TDreamServerShellCommand_DeleteObjects());
		AddCommand(new TDreamServerShellCommand_DeletePlayerItem());
		AddCommand(new TDreamServerShellCommand_DeletePlayerItems());
		AddCommand(new TDreamServerShellCommand_DropPlayer());
		AddCommand(new TDreamServerShellCommand_DropPlayerItem());
		AddCommand(new TDreamServerShellCommand_DropPlayerItems());
		AddCommand(new TDreamServerShellCommand_DryPlayer());
		AddCommand(new TDreamServerShellCommand_ExportItems());
		AddCommand(new TDreamServerShellCommand_FeedPlayer());
		AddCommand(new TDreamServerShellCommand_GodMode());
		AddCommand(new TDreamServerShellCommand_HealPlayer());
		AddCommand(new TDreamServerShellCommand_Help());
		AddCommand(new TDreamServerShellCommand_KickPlayer());
		AddCommand(new TDreamServerShellCommand_KillAnimals());
		AddCommand(new TDreamServerShellCommand_KillPlayer());
		AddCommand(new TDreamServerShellCommand_KillZombies());
		AddCommand(new TDreamServerShellCommand_NotifyAll());
		AddCommand(new TDreamServerShellCommand_NotifyPlayer());
		AddCommand(new TDreamServerShellCommand_PlayerItems());
		AddCommand(new TDreamServerShellCommand_PlayerList());
		AddCommand(new TDreamServerShellCommand_RaisePlayer());
		AddCommand(new TDreamServerShellCommand_Shutdown());
		AddCommand(new TDreamServerShellCommand_Version());
		AddCommand(new TDreamServerShellCommand_VomitPlayer());
		AddCommand(new TDreamServerShellCommand_Welcome());
	}
}