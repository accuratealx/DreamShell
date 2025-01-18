class TDreamServerShellCommandData: Managed
{
	TDreamServerShellCommandList CommandList;	//Список команд
	TDreamSreverShellAdmins AdminList;			//Список id администраторов
	PlayerBase Initiator;						//Ссылка на инициатора
	string Version = "";						//Версия оболочки
	TDreamServerShellCommandLine Command;		//Ссылка на разобранную команду
	
	void TDreamServerShellCommandData(TDreamServerShellCommandList cmdList,	TDreamSreverShellAdmins admList, PlayerBase initiator, string ver, TDreamServerShellCommandLine cmd)
	{
		CommandList = cmdList;
		AdminList = AdminList;
		Initiator = initiator;
		Version = ver;
		Command = cmd;
	}
}