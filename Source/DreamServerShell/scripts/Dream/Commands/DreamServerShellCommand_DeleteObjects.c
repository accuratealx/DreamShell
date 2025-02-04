class TDreamServerShellCommand_DeleteObjects: TDreamServerShellCommand
{
	void TDreamServerShellCommand_DeleteObjects()
	{
		Name = "DeleteObjects";
		Description = "Delete objects around player";
		MinimalParamCount = 0;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: DeleteObjects <Radius>");
		result.Insert("Parameters:");
		result.Insert("  Radius - Search radius (default 10 meters)");
		return result;
	}	
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		int r = data.Command.GetIntParamByIndex(0, 5);
		
		array<Object> items = new array<Object>;
		array<CargoBase> cargoBase = new array<CargoBase>;
		GetGame().GetObjectsAtPosition(data.Initiator.GetPosition(), r, items, cargoBase);
		
		int cnt = 0;
		for (int i = 0; i < items.Count(); i++)
		{
			ItemBase obj = ItemBase.Cast(items.Get(i));
			if (!obj)
				continue;
			
			GetGame().ObjectDelete(obj);
			cnt++;
		}
		
		result.Result.Insert(string.Format("Delete %1 objects", cnt.ToString()));
		return result;
	}
}