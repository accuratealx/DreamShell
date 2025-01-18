class TDreamServerShellBase: Managed
{
	void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx) {};
}

private ref TDreamServerShellBase FDreamServerShellBase;
TDreamServerShellBase DreamServerShellBase()
{
	if (FDreamServerShellBase == null)
		FDreamServerShellBase = new TDreamServerShellBase();
	return FDreamServerShellBase;
}