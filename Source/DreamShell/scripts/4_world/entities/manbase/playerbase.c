modded class PlayerBase
{
	private ref TDreamShellMenu FDreamShell;
	
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		
		if (FDreamShell)
			FDreamShell.OnRPC(sender, rpc_type, ctx);
	}
	
	void DreamShellMenuOpen()
	{
		if (!FDreamShell)
		{
			FDreamShell = new TDreamShellMenu(this);
			FDreamShell.Show();
		}
	}
	
	void DreamShellMenuClose()
	{
		if (FDreamShell)
		{
			FDreamShell.Hide();
			FDreamShell = null;
		}
	}
}