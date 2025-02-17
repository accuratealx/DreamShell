class TDreamShellHelper: Managed
{
	//Прием запросов от сервера
	void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		switch (rpc_type)
		{
			//Вывести уведомление сверху для всех игроков
			case RPC_DREAM_SHELL_SEND_MESSAGE:
				//Duration, Message, Icon
				Param3<float, string, string> prm3 = new Param3<float, string, string>(0, "", "");
				if (ctx.Read(prm3))
					NotificationSystem.AddNotificationExtended(prm3.param1, "#DREAM_SHELL_NOTIFY_TITLE", prm3.param2, prm3.param3);
			break;
		}
	}
}