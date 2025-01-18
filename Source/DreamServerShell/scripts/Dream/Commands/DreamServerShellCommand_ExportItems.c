class TDreamServerShellCommand_ExportItems: TDreamServerShellCommand
{
	void TDreamServerShellCommand_ExportItems()
	{
		Name = "ExportItems";
		Description = "Export items to file";
		MinimalParamCount = 0;
	}

	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: ExportItems");
		return result;
	}
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		string path = DreamShell_GetProfileDir() + "Dream_ExportItem.dzmtib";
		result.Error = DreamShell_SaveStringArrayToFile(GetItemList(), path);

		return result;
	}
	
	private TStringArray GetItemList()
	{
		TStringArray configs = new TStringArray;
		configs.Insert(CFG_VEHICLESPATH);
		configs.Insert(CFG_WEAPONSPATH);
		configs.Insert(CFG_MAGAZINESPATH);
		
		TStringArray list = new TStringArray();
		
		for (int i = 0; i < configs.Count(); i++)
		{
			string CfgPath = configs.Get(i);
			
			for (int j = 0; j < GetGame().ConfigGetChildrenCount(CfgPath); j++)
			{
				string cfgName = "";
				GetGame().ConfigGetChildName(CfgPath, j, cfgName);
				
				string cfgDisplayName = "";
				GetGame().ConfigGetText(CfgPath + " " + cfgName + " displayName", cfgDisplayName);
				
				string cfgDescriptionShort = "";
				GetGame().ConfigGetText(CfgPath + " " + cfgName + " descriptionShort", cfgDescriptionShort);
				
				if (cfgDisplayName.Trim() == "")
					continue;
				
				if (cfgDisplayName.Contains("$UNT$"))
					continue;
				
				int cn = 10;
				cfgDisplayName.Replace("\r", " ");
				cfgDisplayName.Replace("\n", " ");
				cfgDescriptionShort.Replace("\r", " ");
				cfgDescriptionShort.Replace("\n", " ");
				
				string s = string.Format("%1;;;%2;;;%3", cfgName, cfgDisplayName, cfgDescriptionShort);
				list.Insert(s);
			}
		}
		
		return list;
	}
}
