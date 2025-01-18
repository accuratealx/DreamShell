class TDreamServerShellCommand_KillAnimals: TDreamServerShellCommand
{
	void TDreamServerShellCommand_KillAnimals()
	{
		Name = "KillAnimals";
		Description = "Kill animals around player";
		MinimalParamCount = 0;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: KillAnimals <Radius>");
		result.Insert("Parameters:");
		result.Insert("  Radius - Search radius (default 100 meters)");
		return result;
	}	
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		int r = 100;
		if (data.Command.ParamCount() > 0)
			r = data.Command.Parameters()[0].ToInt();
		
		array<Object> items = new array<Object>;
		array<CargoBase> cargoBase = new array<CargoBase>;
		GetGame().GetObjectsAtPosition(data.Initiator.GetPosition(), r, items, cargoBase);
		
		int cnt = 0;
		for (int i = 0; i < items.Count(); i++)
		{
			Object obj = items.Get(i);
			
			if (!obj.IsKindOf("AnimalBase"))
				continue;
			
			EntityAI ZombieAI = EntityAI.Cast(obj);
			if (ZombieAI)
			{
				cnt++;
				ZombieAI.SetHealth(0);
			}
		}
		
		result.Result.Insert(string.Format("Kill %1 animals", cnt.ToString()));
		return result;
	}
}