class TDreamServerShellCommandLine: Managed
{
	private string FRawCommand;
	
	private string FCommandName = "";
	private string FParamString = "";
	private ref TStringArray FParameters = new TStringArray();
	
	
	void TDreamServerShellCommandLine(string command)
	{
		FRawCommand = command.Trim();
		Parse(FRawCommand);
	}
	
	private void Parse(string command)
	{
		TStringArray list = new TStringArray();
		
		bool fquote = false;
		string part = "";
		for (int i = 0; i < command.Length(); i++)
		{
			string s = command.Get(i);
			
			if (s == "'")
			{
				fquote = !fquote;
				continue;
			}
			
			if (s != " ")
			{
				part = part + s;
				continue
			}
			
			if (s == " ")
			{
				if (fquote)
					part = part + s;
				else {
					if (part.Length() != 0)
					{
						list.Insert(part.Trim());
						part = "";
					}
				}
			}
		}
		
		if (part.Length() != 0)
			list.Insert(part.Trim());
		
		//Запомним имя
		if (list.Count() > 0)
			FCommandName = list.Get(0);
		
		//Запомним строку без имени команды
		for (int k = FCommandName.Length(); k < FRawCommand.Length(); k++)
			FParamString = FParamString + FRawCommand[k];
		
		//Запишем параметры
		for (int j = 1; j < list.Count(); j++)
			FParameters.Insert(list.Get(j));
	}
	
	//Имя команды
	string CommandName()
	{
		return FCommandName;
	}
	
	//Строка со всеми парамтрами как пришла с клиента
	string ParamString()
	{
		return FParamString;
	}
	
	//Массив параметров
	TStringArray Parameters()
	{
		return FParameters;
	}
	
	int ParamCount()
	{
		return FParameters.Count();
	}
	
	//Получить булевское значение по номеру параметра
	bool GetBoolParamByIndex(int prmIdx)
	{
		if (prmIdx < 0 || prmIdx > FParameters.Count() - 1)
			return false;
		
		string prm = FParameters.Get(prmIdx);
		prm.Trim();
		prm.ToLower();
		return prm == "yes" || prm == "1" || prm == "on";
	}
	
	int GetIntParamByIndex(int prmIdx, int defValue = -1)
	{
		if (prmIdx < 0 || prmIdx > FParameters.Count() - 1)
			return defValue;
		return FParameters.Get(prmIdx).ToInt();
	}
}