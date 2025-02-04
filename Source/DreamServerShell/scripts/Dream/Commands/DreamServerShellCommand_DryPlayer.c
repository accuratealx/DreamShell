class TDreamServerShellCommand_DryPlayer: TDreamServerShellCommand
{
	void TDreamServerShellCommand_DryPlayer()
	{
		Name = "DryPlayer";
		Description = "Show system version";
		MinimalParamCount = 0;
	}
	
	override TStringArray Help()
	{
		TStringArray result = new TStringArray();
		result.Insert("Name: " + Name);
		result.Insert("Description: " + Description);
		result.Insert("Example: DryPlayer [PlayerID]");
		result.Insert("Parameters:");
		result.Insert("  PlayerID - ID player from PlayerList");
		return result;
	}	
	
	override TDreamServerShellCommandResult Execute(TDreamServerShellCommandData data)
	{
		TDreamServerShellCommandResult result = new TDreamServerShellCommandResult();
		
		string id = data.Command.GetStrParamByIndex(0);
		PlayerBase player = GetPlayerByID(id);
		if (!player)
			result.Error = string.Format(ERROR_PLAYER_NOT_FOUND_FMT, id);
		else {
			GameInventory inv = player.GetInventory();
			if (inv) {
				//Список всех предметов игрока
				array<EntityAI> items = new array<EntityAI>();
				inv.EnumerateInventory(InventoryTraversalType.PREORDER, items);
				
				//Уберем влажность у предметов
				for (int i = 0; i < items.Count(); i++)
				{
					ItemBase item = ItemBase.Cast(items.Get(i));
					if (item)
						item.SetWet(0);
				}
			} else {
				//Тут нет инвентаря у игрока
				result.Error = ERROR_CANT_GET_INVENTORY;
			}
			
		};
		
		return result;
	}
}