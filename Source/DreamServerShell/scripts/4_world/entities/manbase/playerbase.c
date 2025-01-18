#ifdef SERVER
modded class PlayerBase
{
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		DreamServerShellBase().OnRPC(sender, rpc_type, ctx);
	}
}
#endif