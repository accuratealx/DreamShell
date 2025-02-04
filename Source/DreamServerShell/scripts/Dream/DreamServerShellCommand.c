//Результат работы команды
class TDreamServerShellCommandResult: Managed
{
	string Error = "";								//Описание ошибки
	ref TStringArray Result = new TStringArray();	//Вывод команды
}

//Базовая команда
class TDreamServerShellCommand: Managed
{
	string Name = "Template";			//Имя команды
	string Description = "Description";	//Описание команды
	int MinimalParamCount = 0;			//Обязательное количество параметров

	//Вернуть описание
	TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Not implemented");
		return result;
	}
			
	//Выполнить команду и вернуть результат
	TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		result.Error = string.Format("Command '%1' not implemented", Name);
		return result;
	}
	

	//-----Дополнительные методы-----
	//Стандартные ошибки
	protected const string ERROR_PLAYER_NOT_FOUND_FMT = "Player ID %1 not found";
	protected const string ERROR_ITEM_NOT_FOUND_FMT = "Item ID %1 not found";
	protected const string ERROR_CANT_GET_INVENTORY = "Cant get player inventory";
	
	//Сообщения
	protected const string ICON_GEAR = "set:dayz_gui image:settings"; 		//Шестерня
	protected const string ICON_MESSAGE = "set:dayz_gui image:icon_forums"; //Сообщение
	protected const int MESSAGE_DURATION = 10;

	//Отослать уведомление всем игрокам
	protected void SendNotify(string message, float duration = 10, string icon = ICON_GEAR)
	{
		array<Man> players = new array<Man>();
		GetGame().GetPlayers(players);
		for (int i = 0; i < players.Count(); i++)
			SendNotifyToPlayer(PlayerBase.Cast(players.Get(i)), message, duration, icon);
	}
	
	//Отослать сообщение конкретному игроку
	protected void SendNotifyToPlayer(PlayerBase player, string message, float duration = 10, string icon = ICON_GEAR)
	{
		//Duration, Message, Icon
		Param3<float, string, string> prm = new Param3<float, string, string>(duration, message, icon);
		player.RPCSingleParam(RPC_DREAM_SHELL_SEND_MESSAGE, prm, true, player.GetIdentity());
	}	
}