modded class TDreamServerShellCommandList
{
	override void RegisterCommands()
	{
		super.RegisterCommands();
		AddCommand(new DreamServerShellCommand_Echo());
	}
}
