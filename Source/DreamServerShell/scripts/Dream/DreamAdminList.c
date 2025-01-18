typedef map<string, bool> TDreamServerShellAdminList;

class TDreamSreverShellAdmins: Managed
{
	private ref TDreamServerShellAdminList FAdminList = new TDreamServerShellAdminList();
	
	string LoadFromFile(string FileName)
	{
		Clear();
		string err = "";
		JsonFileLoader<TDreamServerShellAdminList>.LoadFile(FileName, FAdminList, err);
		return err;
	}
	
	string SaveToFile(string FileName)
	{
		string err = "";
		JsonFileLoader<TDreamServerShellAdminList>.SaveFile(FileName, FAdminList, err);
		return err;
	}
	
	void Add(string Name)
	{
		FAdminList.Set(Name, false);
	}
	
	void Clear()
	{
		FAdminList.Clear();
	}
	
	float Exist(string itemName)
	{
		bool v;
		return FAdminList.Find(itemName, v);
	}
	
	void DumpToLog()
	{
		Print("");
		DreamShell_Log("TDreamSreverShellAdmins:");
		DreamShell_Log("  Count = " + FAdminList.Count().ToString());
		DreamShell_Log("  Items:");
		for (int i = 0; i < FAdminList.Count(); i++)
		{
			string Name = FAdminList.GetKey(i);
			DreamShell_Log("    " + Name);
		}
	}
}
