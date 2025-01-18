class TDreamShellCommandHistory: Managed
{
	private ref TStringArray FList = new TStringArray();
	private int FMaxLines = 30;
	private int FCurrentIndex = 0;
	
	string SaveToFile(string FileName)
	{
		FileHandle handle = OpenFile(FileName, FileMode.WRITE);
		if (handle == 0)
			return "cant save file " + FileName;
		
		for (int i = 0; i < FList.Count(); i++)
			FPrintln(handle, FList.Get(i));
		
		CloseFile(handle);
		return "";
	}
	
	string LoadFromFile(string FileName)
	{
		FList.Clear();
		
		FileHandle handle = OpenFile(FileName, FileMode.READ);
		if (handle == 0)
			return "cant load file " + FileName;
		
		string line;
		while (FGets(handle, line) > 0)
			FList.Insert(line);

		CloseFile(handle);
		
		FCurrentIndex = FList.Count();
		return "";
	}
	
	private bool IsLastCommandEqual(string cmd)
	{
		if (FList.Count() > 0)
		{
			string line = FList.Get(FList.Count() - 1);
			return line == cmd;
		}
		return false;
	}
	
	void Add(string cmd)
	{
		cmd.Trim();
		if (cmd == "")
			return;
		
		//Не добавлять дубликат
		if (!IsLastCommandEqual(cmd))
			FList.Insert(cmd);
		
		//Почистить старые
		if (FList.Count() > FMaxLines)
			FList.RemoveOrdered(0);
		
		//Поправить последний индекс
		FCurrentIndex = FList.Count();
	}
	
	string GetPrevious()
	{
		if (FList.Count() == 0)
			return "";
	
		FCurrentIndex--;
		if (FCurrentIndex < 0)
			FCurrentIndex = 0;
	
		return FList.Get(FCurrentIndex);		
	}
	
	string GetNext()
	{
		int c = FList.Count();
		if (c == 0)
  			return "";

		FCurrentIndex++;
		if (FCurrentIndex >= c)
			FCurrentIndex = c - 1;

		return FList.Get(FCurrentIndex);
	}
}