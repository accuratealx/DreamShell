const string DREAM_SHELL_VERSION = "0.5.1";

class TDreamServerShell: TDreamServerShellBase
{
	//Каталоги
	private string SETTINGS_DIR;
	private const string ADMIN_FILE = "admin.list";
	
	//Список команд оболочки
	private ref TDreamServerShellCommandList FCommandList = new TDreamServerShellCommandList();
	
	//Список администраторов
	private ref TDreamSreverShellAdmins FAdminList = new TDreamSreverShellAdmins();
	
	void TDreamServerShell()
	{
		//Каталоги
		SETTINGS_DIR = DreamShell_GetProfileDir() + "Dream/Shell/";
		
		//Создать цепочку каталогов
		DreamShell_ForceDirectories(SETTINGS_DIR);
		
		//Спиcок администраторов
		string pCfg = SETTINGS_DIR + ADMIN_FILE;
		if (FileExist(pCfg))
			LoadAdminList(pCfg);
		else
			NewAdminList(pCfg);
		
		
		DreamShell_Log("DreamServerShell init" + " v" + DREAM_SHELL_VERSION);
		FAdminList.DumpToLog();
		FCommandList.DumpToLog();
	}
	
	private void LoadAdminList(string file)
	{
		string err = FAdminList.LoadFromFile(file);
		if (err != "")
			DreamShell_LogEror(err, "DreamServerShell");
	}
	
	private void NewAdminList(string file)
	{
		FAdminList.Clear();
		FAdminList.Add("76561199195178195");
		
		string err = FAdminList.SaveToFile(file);
		if (err != "")
			DreamShell_LogEror(err, "DreamServerShell");
	}
	
	private bool IsPublicCommand(TDreamServerShellCommand cmd)
	{
		TStringArray list = {
			"welcome",
			"help",
			"version",
			"autor"
		};
		
		string cmdName = DreamShell_StrToLower(cmd.Name);
		return list.Find(cmdName) != -1;
	}
	
	private bool IsUserCanExecute(string ID, TDreamServerShellCommand cmd)
	{
		if (IsPublicCommand(cmd))
			return true;
		
		//TODO добавить систему привелегий и команды
		if (FAdminList.Exist(ID))
			return true;
		
		return false;
	}
	
	private void ExecuteCommand(PlayerIdentity sender, string command)
	{
		//Парсим команду
		TDreamServerShellCommandLine cmd = new TDreamServerShellCommandLine(command);
		
		//Выход если делать нечего
		if (cmd.CommandName() == "")
		{
			//Пустая команда
			SendErrorToClient(sender, "Empty command");
			return;
		}

		//Найти команду в списке
		TDreamServerShellCommand CmdExecutor = FCommandList.GetCommand(cmd.CommandName());
		if (CmdExecutor == null)
		{
			//Неизвестная команда
			SendErrorToClient(sender, string.Format("Unknown command '%1'", cmd.CommandName()));
			return;
		}
		
		//Найти пользователя
		PlayerBase player = PlayerBase.Cast(sender.GetPlayer());
		string ID = DreamShell_GetSteamID(player);
		
		//Проверить может ли пользователь выполнять данную команду
		if (!IsUserCanExecute(ID, CmdExecutor))
		{
			//Нет прав на выполнение команды
			SendErrorToClient(sender, string.Format("No permission to execute command '%1'", cmd.CommandName()));
			return;
		}
		
		//Проверить минимальное количество параметров
		if (cmd.ParamCount() < CmdExecutor.MinimalParamCount)
		{
			//Нехватает обязательных параметров
			SendErrorToClient(sender, string.Format("The required parameters are missing '%1'", cmd.CommandName()));
			return;
		}
		
		//Подготовить данные
		TDreamServerShellCommandData data = new TDreamServerShellCommandData(FCommandList, FAdminList, player, DREAM_SHELL_VERSION,	cmd);
		
		//Выполнить команду
		TDreamServerShellCommandResult result = CmdExecutor.Execute(data);
		
		//Отправить результат
		SendResultToClient(sender, result);
	}
	
	private void SendErrorToClient(PlayerIdentity sender, string error)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		result.Error = error;
		SendResultToClient(sender, result);
	}
	
	//Отправка строк на клиент
	private void SendResultToClient(PlayerIdentity sender, TDreamServerShellCommandResult result)
	{
		auto player = sender.GetPlayer();
		
		//Если есть ошибка, вернем только ошибку
		if (result.Error != "")
		{
			player.RPCSingleParam(RPC_DREAM_SHELL_SEND_RESULT, new Param1<string>("ERROR: " + result.Error), true, sender);
			return;
		}

		//Отсылка параметров
		if (result.Result.Count() == 0)
		{
			string msg = "OK";
			player.RPCSingleParam(RPC_DREAM_SHELL_SEND_RESULT, new Param1<string>(msg), true, sender);
		} else {
			for (int i = 0; i < result.Result.Count(); i++)
				player.RPCSingleParam(RPC_DREAM_SHELL_SEND_RESULT, new Param1<string>(result.Result.Get(i)), true, sender);
		}
	}
	
	//Прием событий
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		if (rpc_type == RPC_DREAM_SHELL_SEND_COMMAND)
		{
			Param1<string> prm = new Param1<string>("");
			if (ctx.Read(prm))
				ExecuteCommand(sender, prm.param1);
		}
	}
}