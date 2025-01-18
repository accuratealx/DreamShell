string DreamShell_StrToLower(string Str)
{
	int i = Str.ToLower();
	return Str;
}

void DreamShell_Log(string Msg)
{
	const string PREFIX = "[Dream] ";
	Print(PREFIX + Msg);
}

void DreamShell_LogEror(string err, string ClassName = "")
{
	string s = "ERROR: ";
	if (ClassName != "")
		s = s + ClassName + ": ";
	s = s + err;
	DreamShell_Log(s);
}

void DreamShell_ForceDirectories(string Directory)
{
	TStringArray parts = new TStringArray;
	Directory.Split("/", parts);
	
	for (int i = 0; i < parts.Count(); i++ )
	{
		//Получить кусок пути
		string path = "";
		for (int j = 0; j <= i; j++)
			path = path + parts.Get(j) + "/";
		
		//Создать каталог
		MakeDirectory(path);
	}
}

string DreamShell_GetSteamID(PlayerBase player)
{
	PlayerIdentity identity = player.GetIdentity();
	if (!identity)
		return "";
	return identity.GetPlainId();
}

string DreamShell_SaveStringArrayToFile(TStringArray list, string filename)
{
	FileHandle Handle = OpenFile(filename, FileMode.WRITE);
	if (Handle == 0)
		return "cant open file";
	
	for (int i = 0; i < list.Count(); i++)
		FPrintln(Handle, list.Get(i));
	
	CloseFile(Handle);
	return "";
}

string DreamShell_IntToStringWithSpaces(int value, int minSpaces = 0)
{
	string s = value.ToString();
	int cnt = minSpaces - s.Length();
	if (cnt > 0)
	{
		for (int i = 0; i < cnt; i++)
			s = " " + s ;
	}		
	return s;
}

string DreamShell_GetProfileDir()
{
	return "$profile:/";
}